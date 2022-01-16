/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iariss <iariss@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 09:52:43 by iariss            #+#    #+#             */
/*   Updated: 2021/09/11 18:07:54 by iariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"

void	init_locks(t_vars *vars)
{
	sem_unlink("/fork");
	vars->fork = sem_open("/fork", O_CREAT, 0664, vars->num_of_forks);
	sem_unlink("/gnrl_lock");
	vars->gnrl_lock = sem_open("/gnrl_lock", O_CREAT, 0664, 0);
	sem_unlink("/dead_lock");
	vars->print_lock = sem_open("/dead_lock", O_CREAT, 0664, 1);
	sem_unlink("/end_lock");
	vars->end_lock = sem_open("/end_lock", O_CREAT, 0664, 1);
	sem_unlink("/eaten");
	vars->eating = sem_open("/eaten", O_CREAT, 0664, 1);
	sem_unlink("/times_eat");
	vars->times_eat = sem_open("/times_eat", O_CREAT, 0664, 0);
	vars->start = currenttime();
	vars->eaten = 0;
}

void	loop_vars(t_costum *costum, int i, t_vars *vars)
{
	costum[i].vars = vars;
	costum[i].index = i + 1;
	costum[i].left = i;
	costum[i].right = i + 1;
	if (costum[i].right >= vars->num_of_philos)
		costum[i].right = 0;
}

void	*eating(void *args)
{
	t_vars	*vars;
	int		nbr;

	nbr = 0;
	vars = (t_vars *)args;
	while (1)
	{
		sem_wait(vars->times_eat);
		nbr++;
		if (nbr == vars->num_of_philos)
		{
			sem_wait(vars->print_lock);
			printf("End\n");
			sem_post(vars->gnrl_lock);
		}
	}
}

int	create_processes(t_vars *vars)
{
	t_costum	*costum;
	int			*pid;
	int			i;
	pthread_t	t;

	i = 0;
	pid = malloc(sizeof(int) * vars->num_of_philos);
	costum = malloc(sizeof(t_costum) * vars->num_of_philos);
	init_locks(vars);
	if (pthread_create(&t, NULL, &eating, vars) != 0)
	{
		print_error("pthread_create error\n");
		return (0);
	}
	pthread_detach(t);
	while (i < vars->num_of_philos)
	{
		pid[i] = fork();
		loop_vars(costum, i, vars);
		if (pid[i] == 0)
			start(&costum[i]);
		i++;
	}
	close_kill(vars, &pid, costum);
	return (1);
}

int	main(int c, char **v)
{
	t_vars	*vars;

	if (c > 4 && c <= 6)
	{
		vars = (t_vars *)malloc(sizeof(t_vars));
		if (!check_arguments(v, vars))
		{
			free(vars);
			return (-1);
		}
		if (!create_processes(vars))
		{
			free(vars);
			return (-1);
		}
		return (0);
	}
	print_error("Error\nNumber Of Arguments\n");
	return (1);
}

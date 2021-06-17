/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iariss <iariss@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 09:52:43 by iariss            #+#    #+#             */
/*   Updated: 2021/06/17 09:40:54 by iariss           ###   ########.fr       */
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
	vars->dead_lock = sem_open("/dead_lock", O_CREAT, 0664, 1);
	sem_unlink("/end_lock");
	vars->end_lock = sem_open("/end_lock", O_CREAT, 0664, 1);
	sem_unlink("/eaten");
	vars->eating = sem_open("/eaten", O_CREAT, 0664, 1);
	sem_unlink("/times_eat");
	vars->times_eat = sem_open("/times_eat", O_CREAT, 0664, 0);
	sem_wait(vars->death_lock);
	vars->start = currenttime();
	vars->eaten = 0;
}

void	loop_vars(t_costum *costum, int i, t_vars *vars)
{
	costum[i - 1].vars = vars;
	costum->vars->dead = 0;
	costum[i - 1].index = i;
	costum[i - 1].left = costum[i - 1].index;
	costum[i - 1].right = costum[i - 1].index + 1;
	if (costum[i - 1].right > vars->num_of_philos)
		costum[i - 1].right = 1;
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
			printf("End\n");
			sem_post(vars->gnrl_lock);
		}
	}
}

int	create_threads(t_vars *vars)
{
	t_costum	*costum;
	int			*pid;
	int			i;
	pthread_t	t;

	i = 1;
	pid = malloc(sizeof(int) * vars->num_of_philos + 1);
	costum = malloc(sizeof(t_costum) * vars->num_of_philos + 1);
	init_locks(vars);
	if (pthread_create(&t, NULL, &eating, vars) != 0)
	{
		print_error("pthread_create error\n");
		return (0);
	}
	pthread_detach(t);
	while (i <= vars->num_of_philos)
	{
		pid[i] = fork();
		loop_vars(costum, i, vars);
		if (pid[i] == 0)
			start(&costum[i - 1]);
		i++;
	}
	close_kill(vars, &pid);
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
		if (!create_threads(vars))
		{
			free(vars);
			return (-1);
		}
		return (0);
	}
	print_error("Error\nNumber Of Arguments\n");
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iariss <iariss@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 15:38:35 by iariss            #+#    #+#             */
/*   Updated: 2021/06/17 09:39:10 by iariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"

void	init_locks(t_vars *vars)
{
	int	i;

	i = 1;
	while (i <= vars->num_of_philos)
	{
		pthread_mutex_init(&vars->fork[i++], NULL);
	}
	pthread_mutex_init(&vars->dead_lock, NULL);
	pthread_mutex_init(&vars->end_lock, NULL);
	pthread_mutex_init(&vars->gnrl_lock, NULL);
	pthread_mutex_init(&vars->eating, NULL);
	pthread_mutex_lock(&vars->gnrl_lock);
	pthread_mutex_lock(&vars->death_lock);
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

int	thread_loop(t_costum *costum, t_vars *vars)
{
	int			i;
	pthread_t	*t;

	i = 1;
	vars->start = currenttime();
	t = malloc(sizeof(pthread_t) * vars->num_of_philos);
	while (i <= vars->num_of_philos)
	{
		loop_vars(costum, i, vars);
		if (pthread_create(&t[i], NULL, &start, &costum[i - 1]) != 0)
		{
			print_error("pthread_create error\n");
			return (0);
		}
		pthread_detach(t[i]);
		usleep(100);
		i++;
	}
	free(t);
	return (1);
}

int	create_threads(t_vars *vars)
{
	t_costum	*costum;

	costum = malloc(sizeof(t_costum) * vars->num_of_philos + 1);
	vars->eaten = 0;
	vars->fork = malloc(sizeof(pthread_mutex_t) * (vars->num_of_philos + 1));
	init_locks(vars);
	if (!thread_loop(costum, vars))
		return (0);
	pthread_mutex_lock(&vars->gnrl_lock);
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
		free(vars);
		return (0);
	}
	print_error("Error\nNumber Of Arguments\n");
	return (1);
}

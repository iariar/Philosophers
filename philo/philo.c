/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iariss <iariss@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 15:38:35 by iariss            #+#    #+#             */
/*   Updated: 2021/09/11 16:20:15 by iariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"

void	init_locks(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->num_of_philos)
	{
		pthread_mutex_init(&vars->fork[i++], NULL);
	}
	pthread_mutex_init(&vars->print_lock, NULL);
	pthread_mutex_init(&vars->end_lock, NULL);
	pthread_mutex_init(&vars->gnrl_lock, NULL);
	pthread_mutex_init(&vars->eating, NULL);
	pthread_mutex_lock(&vars->gnrl_lock);
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

int	thread_loop(t_costum *costum, t_vars *vars)
{
	int			i;
	pthread_t	*t;

	i = 0;
	vars->start = currenttime();
	t = malloc(sizeof(pthread_t) * vars->num_of_philos);
	while (i < vars->num_of_philos)
	{
		loop_vars(costum, i, vars);
		if (pthread_create(&t[i], NULL, &start, &costum[i]) != 0)
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
	int			i;

	costum = malloc(sizeof(t_costum) * vars->num_of_philos);
	vars->eaten = 0;
	vars->fork = malloc(sizeof(pthread_mutex_t) * (vars->num_of_philos));
	init_locks(vars);
	if (!thread_loop(costum, vars))
		return (0);
	pthread_mutex_lock(&vars->gnrl_lock);
	i = 0;
	while (i < vars->num_of_philos)
		pthread_mutex_destroy(&vars->fork[i++]);
	pthread_mutex_destroy(&vars->print_lock);
	pthread_mutex_destroy(&vars->end_lock);
	pthread_mutex_destroy(&vars->gnrl_lock);
	pthread_mutex_destroy(&vars->eating);
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
		return (1);
	}
	print_error("Error\nNumber Of Arguments\n");
	return (-1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iariss <iariss@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 12:09:53 by iariss            #+#    #+#             */
/*   Updated: 2021/06/16 20:44:56 by iariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"

long	currenttime(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec * 0.001);
}

void	lock_print(char *s, t_costum *costum)
{
	int	diff;

	pthread_mutex_lock(&costum->vars->dead_lock);
	diff = currenttime() - costum->vars->start;
	printf(s, diff, costum->index);
	pthread_mutex_unlock(&costum->vars->dead_lock);
}

void	philo_life(t_costum *costum)
{
	while (1)
	{
		pthread_mutex_lock(&costum->vars->fork[costum->left]);
		lock_print("%ld philosopher %d has taken a fork\n", costum);
		pthread_mutex_lock(&costum->vars->fork[costum->right]);
		lock_print("%ld philosopher %d has taken a fork\n", costum);
		lock_print("%ld philosopher %d is eating\n", costum);
		costum->time_limit = currenttime() + costum->vars->time_to_die;
		usleep(costum->vars->time_to_eat * 1000);
		pthread_mutex_lock(&costum->vars->eating);
		costum->vars->eaten++;
		pthread_mutex_unlock(&costum->vars->eating);
		pthread_mutex_unlock(&costum->vars->fork[costum->right]);
		pthread_mutex_unlock(&costum->vars->fork[costum->left]);
		lock_print("%ld philosopher %d is sleeping\n", costum);
		usleep(costum->vars->time_to_sleep * 1000);
		lock_print("%ld philosopher %d is thinking\n", costum);
	}
}

void	*death_checker(void *var)
{
	t_costum	*costum;

	costum = (t_costum *)var;
	while (1)
	{
		if (currenttime() > costum->time_limit)
		{
			pthread_mutex_lock(&costum->vars->dead_lock);
			printf("%d died \n", costum->index);
			pthread_mutex_unlock(&costum->vars->gnrl_lock);
			return (NULL);
		}
		if (costum->vars->num_times_eat != -1
			&& costum->vars->eaten >= costum->vars->num_times_eat
			* costum->vars->num_of_philos)
		{
			pthread_mutex_lock(&costum->vars->dead_lock);
			printf("end\n");
			pthread_mutex_unlock(&costum->vars->gnrl_lock);
		}
		usleep(500);
	}
	return (NULL);
}

void	*start(void	*args)
{
	t_costum	*costum;
	pthread_t	t;

	costum = (t_costum *)args;
	costum->time_limit = currenttime() + costum->vars->time_to_die;
	pthread_create(&t, NULL, &death_checker, (void *)costum);
	pthread_detach(t);
	philo_life(costum);
	return (NULL);
}

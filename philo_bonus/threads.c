/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iariss <iariss@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 12:09:53 by iariss            #+#    #+#             */
/*   Updated: 2021/06/16 20:46:43 by iariss           ###   ########.fr       */
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

	sem_wait(costum->vars->dead_lock);
	diff = currenttime() - costum->vars->start;
	printf(s, diff, costum->index);
	sem_post(costum->vars->dead_lock);
}

void	philo_life(t_costum *costum)
{
	int	n;

	n = 0;
	while (1)
	{
		sem_wait(costum->vars->fork);
		lock_print("%ld philosopher %d has taken a fork\n", costum);
		sem_wait(costum->vars->fork);
		lock_print("%ld philosopher %d has taken a fork\n", costum);
		lock_print("%ld philosopher %d is eating\n", costum);
		n++;
		if (n == costum->vars->num_times_eat)
			sem_post(costum->vars->times_eat);
		costum->time_limit = currenttime() + costum->vars->time_to_die;
		usleep(costum->vars->time_to_eat * 1000);
		sem_post(costum->vars->fork);
		sem_post(costum->vars->fork);
		sem_post(costum->vars->eating);
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
			sem_wait(costum->vars->dead_lock);
			printf("%d died \n", costum->index);
			sem_post(costum->vars->gnrl_lock);
			exit(0);
			return (NULL);
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

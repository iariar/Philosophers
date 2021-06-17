/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iariss <iariss@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 15:38:35 by iariss            #+#    #+#             */
/*   Updated: 2021/06/14 12:14:05 by iariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"

int	ft_atoi(const char *str)
{
	long int	res;
	int			sign;
	int			i;

	res = 0;
	sign = 1;
	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\v'
			|| str[i] == '\f' || str[i] == '\r' || str[i] == '\n'))
		i++;
	if (str[i] == '-' && str[i])
		sign = -1;
	if ((str[i] == '-' || str[i] == '+') && str[i])
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		if (res > 2147483647 && sign == 1)
			return (-1);
		if (res > 2147483648 && sign == -1)
			return (0);
		i++;
	}
	return (sign * res);
}

int		ft_strlen(char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	print_error(char *s)
{
	int i;

	i= 0;
	while (s[i])
	{
		write(2, &s[i], 1);
		i++;
	}
}

void	print_message(char *s)
{
	int i;

	i= 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
}

void	varso(int i, char **v, t_vars *vars)
{
	vars->num_of_philos = ft_atoi(v[1]);
	vars->num_of_philos = ft_atoi(v[1]);
	vars->time_to_die = ft_atoi(v[2]);
	vars->time_to_eat = ft_atoi(v[3]);
	vars->time_to_sleep = ft_atoi(v[4]);
	if (i == 6)
		vars->num_times_eat = ft_atoi(v[5]);
	else
		vars->num_times_eat = INT_MAX;
}

int	check_arguments(char **v, t_vars *vars)
{
	int i;
	int j;

	i = 1;
	j = 0;
	while(v[i])
	{
		if (v[i][0] == '-' || (v[i][0] == '0' && ft_strlen(v[i]) == 1))
		{
			print_error("Error\nNegative Number Or Zero\n");
			return (0);
		}
		j = 0;
		while (v[i][j])
		{
			if (v[i][j] >= '0' && v[i][j] <= '9')
				j++;
			else
			{
				print_error("Error\nBad Character\n");
				return (0);
			}
		}
		i++;
	}
	varso(i, v, vars);
	return (1);
}

long	currenttime()
{
	struct	timeval	time;
	
	gettimeofday(&time, NULL);
	return(time.tv_sec * 1000 + time.tv_usec * 0.001);
}

// void	print_msg_locked(char *s, t_costum *costum)
// {
// 	pthread_mutex_lock(&costum->vars->dead_lock);
// 	print_error(s);	
// 	pthread_mutex_unlock(&costum->vars->dead_lock);
// }

void	*death_checker(void *var)
{
	t_costum *costum;

	costum = (t_costum *)var;
	while(1)
	{
		if (currenttime() > costum->time_limit)
		{
			pthread_mutex_lock(&costum->vars->dead_lock);
			printf("%d died \n", costum->index);
			pthread_mutex_unlock(&costum->vars->gnrl_lock);
			return (NULL);
		}
		usleep(500);
	}
	return (NULL);
}

void	lock_print(char *s, t_costum *costum)
{
	int diff;

	pthread_mutex_lock(&costum->vars->dead_lock);
	diff = currenttime() - costum->vars->start;
	printf(s, diff, costum->index);
	pthread_mutex_unlock(&costum->vars->dead_lock);
}

void	philo_life(t_costum *costum)
{
	int times = 0;

	while (1)
	{
		pthread_mutex_lock(&costum->vars->fork[costum->left]);
		lock_print("%ld philosopher %d has taken a fork\n", costum);
		pthread_mutex_lock(&costum->vars->fork[costum->right]);
		lock_print("%ld philosopher %d has taken a fork\n", costum);
		lock_print("%ld philosopher %d is eating\n", costum);
		costum->time_limit = currenttime() + costum->vars->time_to_die;
		usleep(costum->vars->time_to_eat * 1000);
		pthread_mutex_unlock(&costum->vars->fork[costum->right]);
		pthread_mutex_unlock(&costum->vars->fork[costum->left]);
		lock_print("%ld philosopher %d is sleeping\n", costum);
		usleep(costum->vars->time_to_sleep * 1000);
		lock_print("%ld philosopher %d is thinking\n", costum);
		pthread_mutex_lock(&costum->vars->end_lock);
		times++;
		if (times >= costum->vars->num_times_eat)
		{
			pthread_mutex_lock(&costum->vars->dead_lock);
			printf("End\n");
			pthread_mutex_unlock(&costum->vars->gnrl_lock);
		}
		pthread_mutex_unlock(&costum->vars->end_lock);
	}
}

void	*start(void	*args)
{
	t_costum *costum;
	pthread_t t;

	costum = (t_costum*)args;
	costum->time_limit = currenttime() + costum->vars->time_to_die;
	pthread_create(&t, NULL, &death_checker, (void *)costum);
	pthread_detach(t);
	philo_life(costum);
	return (NULL);
}

void	init_locks(t_vars *vars)
{
	int i;

	i = 0;
	while (i <= vars->num_of_philos)
	{
		pthread_mutex_init(&vars->fork[i++], NULL);
	}
	pthread_mutex_init(&vars->dead_lock, NULL);
	pthread_mutex_init(&vars->end_lock, NULL);
	pthread_mutex_init(&vars->gnrl_lock, NULL);
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
	int i;
	pthread_t t[vars->num_of_philos];

	i = 1;
	vars->start = currenttime();
	while (i <= vars->num_of_philos)
	{
		loop_vars(costum, i, vars);
		if (pthread_create(&t[i], NULL, &start, &costum[i - 1]) != 0)
		{
			// free(costum);
			// free(vars->fork);
			print_error("pthread_create error\n");
			return(0);
		}
		pthread_detach(t[i]);
		usleep(100);
		i++;
	}
	return (1);
}

int	create_threads(t_vars *vars)
{
	int i;
	pthread_t t[vars->num_of_philos];
	t_costum *costum;

	costum = malloc(sizeof(t_costum) * vars->num_of_philos + 1);
	vars->fuel = 0;
	vars->fork = malloc(sizeof(pthread_mutex_t) * (vars->num_of_philos + 1));
	init_locks(vars);
	if (!thread_loop(costum, vars))
		return (0);
	pthread_mutex_lock(&vars->gnrl_lock);
	// free(costum);
	// free(vars->fork);
	return(1);
}


int	main(int c, char **v)
{
	t_vars *vars;

	if (c > 4 && c <= 6)
	{
		vars = (t_vars *)malloc(sizeof(t_vars));
		vars->mutex_test = 0;	
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iariss <iariss@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 15:47:13 by iariss            #+#    #+#             */
/*   Updated: 2021/06/16 11:35:56 by iariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_H
# define FILE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_vars
{
	int				num_of_philos;
	int				indicate;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_times_eat;
	int				mutex_test;
	int				num_of_forks;
	pthread_mutex_t	*fork;
	pthread_mutex_t	gnrl_lock;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	end_lock;
	pthread_mutex_t	eating;
	struct timeval	time;
	int				fuel;
	long int		start;
	long int		end;
	int				dead;
	long int		current;
	int				eaten;
}				t_vars;

typedef struct s_costum
{
	int			index;
	long		time_limit;
	int			nmeal;
	int			left;
	int			right;
	long int	start;
	long int	end;
	t_vars		*vars;
}				t_costum;

int		num_check(char **v, int i);
int		check_arguments(char **v, t_vars *vars);
int		ft_atoi(const char *str);
int		ft_strlen(char *s);
long	currenttime(void);
void	lock_print(char *s, t_costum *costum);
void	print_msg_locked(char *s, t_costum *costum);
void	varso(int i, char **v, t_vars *vars);
void	print_error(char *s);
void	print_message(char *s);
void	*death_checker(void *var);
void	philo_life(t_costum *costum);
void	*start(void	*args);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iariss <iariss@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 12:05:45 by iariss            #+#    #+#             */
/*   Updated: 2021/09/11 18:05:52 by iariss           ###   ########.fr       */
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

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	print_error(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(2, &s[i], 1);
		i++;
	}
}

void	print_message(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
}

void	close_kill(t_vars *vars, int **pid, t_costum *costum)
{
	int	i;

	i = 1;
	sem_wait(vars->gnrl_lock);
	sem_close(vars->gnrl_lock);
	sem_close(vars->fork);
	sem_close(vars->print_lock);
	sem_close(vars->end_lock);
	i = 0;
	while (i < vars->num_of_philos)
	{
		kill((*pid)[i], SIGKILL);
		i++;
	}
	free(*pid);
	free(vars);
	free(costum);
}

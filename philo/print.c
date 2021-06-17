/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iariss <iariss@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 12:05:45 by iariss            #+#    #+#             */
/*   Updated: 2021/06/15 09:12:25 by iariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"

void	print_msg_locked(char *s, t_costum *costum)
{
	pthread_mutex_lock(&costum->vars->dead_lock);
	print_error(s);
	pthread_mutex_unlock(&costum->vars->dead_lock);
}

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

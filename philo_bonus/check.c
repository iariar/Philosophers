/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iariss <iariss@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 12:01:52 by iariss            #+#    #+#             */
/*   Updated: 2021/07/26 10:38:25 by iariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"

void	varso(int i, char **v, t_vars *vars)
{
	vars->num_of_philos = ft_atoi(v[1]);
	vars->time_to_die = ft_atoi(v[2]);
	vars->time_to_eat = ft_atoi(v[3]);
	vars->time_to_sleep = ft_atoi(v[4]);
	if (i == 6)
		vars->num_times_eat = ft_atoi(v[5]);
	else
		vars->num_times_eat = -1;
	vars->num_of_forks = vars->num_of_philos;
}

int	num_check(char **v, int i)
{
	if (ft_atoi(v[i]) == 0)
	{
		print_error("Error\nArgumant Should not be zero\n");
		return (0);
	}
	if (ft_atoi(v[i]) < 0)
	{
		print_error("Error\nArgumant Should not be Negative\n");
		return (0);
	}
	return (1);
}

int	check_arguments(char **v, t_vars *vars)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (v[i])
	{
		j = 0;
		while (v[i][j])
		{
			if ((v[i][j] >= '0' && v[i][j] <= '9')
			|| (v[i][j] == '-' && j == 0))
				j++;
			else
			{
				print_error("Error\nBad Character\n");
				return (0);
			}
		}
		if (!num_check(v, i))
			return (0);
		i++;
	}
	varso(i, v, vars);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iariss <iariss@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 10:16:01 by iariss            #+#    #+#             */
/*   Updated: 2021/06/09 13:27:18 by iariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void	*test_func()
{
	// printf("in the thread\n");
	// sleep(2);
	// printf("out\n");
	return (NULL);
}

int main()
{
	pthread_t t[10];
	int i;

	i = 0;
	while (i < 10)
	{
		pthread_create(&t[i], NULL, &test_func, NULL);
		printf("thread %d has started\n", i);
		i++;
	}
	i = 0;
	while (i < 10)
	{
		pthread_join(t[i], NULL);
		printf("thread %d has ended\n", i);
		i++;
	}
	return (0);
}

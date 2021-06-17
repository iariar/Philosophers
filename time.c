/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iariss <iariss@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 11:01:18 by iariss            #+#    #+#             */
/*   Updated: 2021/06/11 11:08:04 by iariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"

int main()
{
	struct timeval time;
	
	gettimeofday(&time, NULL);
	printf("seconds = %ld\nmicliseconds = %d\n", time.tv_sec, time.tv_usec);
}
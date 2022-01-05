/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tel-bara <tel-bara@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/01 13:56:52 by tel-bara      #+#    #+#                 */
/*   Updated: 2021/09/09 15:57:04 by tel-bara      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>
#include "proto.h"

unsigned long	ft_atoi(char *str)
{
	unsigned long	res;

	res = 0;
	while (*str)
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	return (res);
}

static unsigned long	time_elapsed(struct timeval *then)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (1000000 * (now.tv_sec - then->tv_sec)
		+ now.tv_usec - then->tv_usec);
}

void	better_usleep(unsigned long sleep_time)
{
	struct timeval	start;
	t_specs			*specs;

	gettimeofday(&start, NULL);
	specs = get_specs();
	while (!specs->death && time_elapsed(&start) < sleep_time)
		usleep(50);
}

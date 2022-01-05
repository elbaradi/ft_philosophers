/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   forks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tel-bara <tel-bara@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/01 13:59:05 by tel-bara      #+#    #+#                 */
/*   Updated: 2021/09/09 18:51:41 by tel-bara      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include "proto.h"

pthread_mutex_t	**get_forks(void)
{
	static pthread_mutex_t	*forks = 0;

	return (&forks);
}

void	set_forks(void)
{
	pthread_mutex_t	**forks;
	t_specs			*specs;
	unsigned long	i;

	forks = get_forks();
	specs = get_specs();
	*forks = (pthread_mutex_t *)malloc(specs->num_philos
			* sizeof(pthread_mutex_t));
	if (*forks == NULL)
	{
		destroy_specs();
		exit (1);
	}
	i = 0;
	while (i < specs->num_philos)
	{
		pthread_mutex_init(&(*forks)[i], NULL);
		i++;
	}
}

void	destroy_forks(void)
{
	pthread_mutex_t	**forks;
	t_specs			*specs;
	unsigned long	i;

	forks = get_forks();
	specs = get_specs();
	i = 0;
	while (i < specs->num_philos)
	{
		pthread_mutex_destroy(&(*forks)[i]);
		i++;
	}
	free(*forks);
}

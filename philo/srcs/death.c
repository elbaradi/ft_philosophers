/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   death.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tel-bara <tel-bara@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/01 18:28:53 by tel-bara      #+#    #+#                 */
/*   Updated: 2021/09/09 15:53:59 by tel-bara      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "proto.h"
#include <unistd.h>
#include <pthread.h>

void	*death_timer(void *ptr)
{
	t_specs			*specs;
	t_philo			*philo;
	unsigned long	timestamp;

	philo = (t_philo *)ptr;
	specs = get_specs();
	pthread_mutex_lock(specs->prompt);
	while (!specs->death && (!specs->max_meals
			|| specs->satisfied < specs->num_philos))
	{
		pthread_mutex_unlock(specs->prompt);
		timestamp = get_timestamp_in_ms();
		better_usleep((specs->time_to_die
				- (timestamp - philo->last_fed)) * 1000);
		timestamp = get_timestamp_in_ms();
		pthread_mutex_lock(specs->prompt);
		if (timestamp - philo->last_fed >= specs->time_to_die)
		{
			philo->state = deceased;
			write_prompt(deceased, philo->index + 1, get_timestamp_in_ms());
			specs->death += 1;
		}
	}
	pthread_mutex_unlock(specs->prompt);
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   death.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tel-bara <tel-bara@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/01 18:28:53 by tel-bara      #+#    #+#                 */
/*   Updated: 2021/09/20 17:01:35 by tel-bara      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <semaphore.h>
#include <unistd.h>
#include "struct.h"
#include "proto.h"

void	*death_timer(void *ptr)
{
	t_specs			*specs;
	t_philo			*philo;
	unsigned long	timestamp;

	philo = (t_philo *)ptr;
	specs = get_specs();
	sem_wait(specs->prompt);
	while (!specs->death)
	{
		sem_post(specs->prompt);
		timestamp = get_timestamp_in_ms();
		better_usleep((specs->time_to_die
				- (timestamp - philo->last_fed)) * 1000);
		timestamp = get_timestamp_in_ms();
		sem_wait(specs->prompt);
		if (timestamp - philo->last_fed >= specs->time_to_die)
		{
			philo->state = deceased;
			specs->death = 1;
			write_prompt(deceased, philo->index + 1, get_timestamp_in_ms());
			break ;
		}
	}
	exit (DEATH_CODE);
}

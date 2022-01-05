/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tel-bara <tel-bara@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/01 12:26:10 by tel-bara      #+#    #+#                 */
/*   Updated: 2021/09/20 17:01:15 by tel-bara      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <semaphore.h>
#include <unistd.h>
#include "structs.h"
#include "proto.h"

void	grab_forks(t_philo *philo)
{
	unsigned long	timestamp;
	t_specs			*specs;	

	specs = get_specs();
	sem_wait(specs->forks);
	philo->state = grabbing_forks;
	timestamp = get_timestamp_in_ms();
	sem_wait(specs->prompt);
	write_prompt(grabbing_forks, philo->index + 1, timestamp);
	sem_post(specs->prompt);
	if (specs->num_philos == 1)
	{
		better_usleep(specs->time_to_die * 1000 + 500);
		return ;
	}
	sem_wait(specs->forks);
	timestamp = get_timestamp_in_ms();
	sem_wait(specs->prompt);
	write_prompt(grabbing_forks, philo->index + 1, timestamp);
	sem_post(specs->prompt);
	return ;
}

void	eat(t_philo *philo)
{
	unsigned long	timestamp;
	t_specs			*specs;

	specs = get_specs();
	timestamp = get_timestamp_in_ms();
	sem_wait(specs->prompt);
	philo->state = eating;
	philo->last_fed = timestamp;
	philo->meals++;
	write_prompt(eating, philo->index + 1, timestamp);
	if (philo->meals == specs->max_meals)
		sem_post(specs->satisfied);
	sem_post(specs->prompt);
	better_usleep(specs->time_to_eat * 1000);
	sem_post(specs->forks);
	if (specs->num_philos == 1)
		return ;
	sem_post(specs->forks);
	return ;
}

void	nap(t_philo *philo)
{
	unsigned long	timestamp;
	t_specs			*specs;

	specs = get_specs();
	sem_wait(specs->prompt);
	timestamp = get_timestamp_in_ms();
	philo->state = sleeping;
	write_prompt(sleeping, philo->index + 1, timestamp);
	sem_post(specs->prompt);
	better_usleep(specs->time_to_sleep * 1000);
	return ;
}

void	think(t_philo *philo)
{
	unsigned long	timestamp;
	t_specs			*specs;

	specs = get_specs();
	sem_wait(specs->prompt);
	timestamp = get_timestamp_in_ms();
	philo->state = thinking;
	write_prompt(thinking, philo->index + 1, timestamp);
	sem_post(specs->prompt);
	return ;
}

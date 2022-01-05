/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tel-bara <tel-bara@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/01 12:26:10 by tel-bara      #+#    #+#                 */
/*   Updated: 2021/09/09 16:51:05 by tel-bara      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "proto.h"
#include <unistd.h>

void	grab_forks(t_philo *philo)
{
	unsigned long	timestamp;
	t_specs			*specs;	

	specs = get_specs();
	if (philo->index % 2 == 1)
		better_usleep(100);
	pthread_mutex_lock(philo->left_fork);
	philo->state = grabbing_forks;
	timestamp = get_timestamp_in_ms();
	write_prompt(grabbing_forks, philo->index + 1, timestamp);
	if (philo->left_fork == philo->right_fork)
	{
		better_usleep(specs->time_to_die * 1000 + 500);
		return ;
	}
	pthread_mutex_lock(philo->right_fork);
	timestamp = get_timestamp_in_ms();
	write_prompt(grabbing_forks, philo->index + 1, timestamp);
	return ;
}

void	eat(t_philo *philo)
{
	unsigned long	timestamp;
	t_specs			*specs;

	specs = get_specs();
	timestamp = get_timestamp_in_ms();
	pthread_mutex_lock(specs->prompt);
	philo->state = eating;
	philo->last_fed = timestamp;
	philo->meals++;
	write_prompt(eating, philo->index + 1, timestamp);
	if (philo->meals == specs->max_meals)
		specs->satisfied++;
	pthread_mutex_unlock(specs->prompt);
	better_usleep(specs->time_to_eat * 1000);
	return ;
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	if (philo->left_fork == philo->right_fork)
		return ;
	pthread_mutex_unlock(philo->left_fork);
	return ;
}

void	nap(t_philo *philo)
{
	unsigned long	timestamp;
	t_specs			*specs;

	specs = get_specs();
	pthread_mutex_lock(specs->prompt);
	timestamp = get_timestamp_in_ms();
	philo->state = sleeping;
	write_prompt(sleeping, philo->index + 1, timestamp);
	pthread_mutex_unlock(specs->prompt);
	better_usleep(specs->time_to_sleep * 1000);
	return ;
}

void	think(t_philo *philo)
{
	unsigned long	timestamp;
	t_specs			*specs;

	specs = get_specs();
	pthread_mutex_lock(specs->prompt);
	timestamp = get_timestamp_in_ms();
	philo->state = thinking;
	write_prompt(thinking, philo->index + 1, timestamp);
	pthread_mutex_unlock(specs->prompt);
	return ;
}

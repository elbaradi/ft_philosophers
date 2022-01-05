/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   simulation.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tel-bara <tel-bara@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/09 15:25:12 by tel-bara      #+#    #+#                 */
/*   Updated: 2021/09/09 18:03:15 by tel-bara      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <pthread.h>
#include "structs.h"
#include "proto.h"

static void	start_routine(t_philo *philo)
{
	t_specs		*specs;
	pthread_t	tid;

	specs = get_specs();
	pthread_create(&tid, NULL, &death_timer, philo);
	pthread_detach(tid);
	while (!specs->death && (!specs->max_meals
			|| specs->satisfied < specs->num_philos))
	{
		grab_forks(philo);
		eat(philo);
		drop_forks(philo);
		nap(philo);
		think(philo);
	}
	return ;
}

static void	init_philo(t_philo *philo)
{
	pthread_mutex_t	**forks;
	t_specs			*specs;

	specs = get_specs();
	philo->meals = 0;
	philo->last_fed = 0;
	philo->state = thinking;
	forks = get_forks();
	philo->right_fork = &(*forks)[philo->index];
	if (philo->index == 0)
		philo->left_fork = &(*forks)[specs->num_philos - 1];
	else
		philo->left_fork = &(*forks)[philo->index - 1];
}

static void	*spawn_philo(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *)arg;
	init_philo(philo);
	start_routine(philo);
	return (0);
}

static void	simulate(t_philo *philos)
{
	unsigned long	i;
	t_specs			*specs;

	specs = get_specs();
	i = 0;
	while (i < specs->num_philos)
	{
		philos[i].index = i;
		if (pthread_create(&philos[i].tid, NULL, spawn_philo, &philos[i]) != 0)
			break ;
		i++;
	}
	if (i != specs->num_philos)
	{
		print_message(THREAD_ERROR);
		specs->death = 1;
	}
	while (i != 0)
	{
		i--;
		pthread_join(philos[i].tid, NULL);
	}
}

void	launch_simulation(void)
{
	t_specs			*specs;
	t_philo			*philos;

	specs = get_specs();
	philos = malloc(specs->num_philos * sizeof(t_philo));
	if (philos == NULL)
		return ;
	print_message(HEADER);
	simulate(philos);
	free(philos);
	print_message(FOOTER);
}

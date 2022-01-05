/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   simulation.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tel-bara <tel-bara@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/09 15:25:12 by tel-bara      #+#    #+#                 */
/*   Updated: 2021/09/20 17:02:32 by tel-bara      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <semaphore.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <pthread.h>
#include <unistd.h>
#include "structs.h"
#include "proto.h"

static void	start_routine(t_philo *philo)
{
	t_specs		*specs;
	pthread_t	tid;

	specs = get_specs();
	pthread_create(&tid, NULL, &death_timer, philo);
	pthread_detach(tid);
	while (1)
	{
		grab_forks(philo);
		eat(philo);
		nap(philo);
		think(philo);
	}
	return ;
}

static void	init_philo(t_philo *philo)
{
	t_specs	*specs;

	specs = get_specs();
	sem_wait(specs->satisfied);
	philo->meals = 0;
	philo->last_fed = 0;
	philo->state = thinking;
}

static void	*spawn_philo(t_philo *philo)
{
	init_philo(philo);
	start_routine(philo);
	exit (0);
}

static void	simulate(t_philo **philos)
{
	unsigned long	i;
	t_specs			*specs;
	t_specs			*specs_p;

	specs = get_specs();
	i = 0;
	while (i < specs->num_philos)
	{
		(*philos)[i].index = i;
		(*philos)[i].pid = fork();
		if ((*philos)[i].pid == 0)
		{
			specs_p = get_specs();
			*specs_p = *specs;
			set_base_timestamp();
			spawn_philo(&(*philos)[i]);
		}
		else if ((*philos)[i].pid == -1)
			break ;
		better_usleep(10);
		i++;
	}
	end_simulation(philos, i);
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
	simulate(&philos);
	free(philos);
	print_message(FOOTER);
}

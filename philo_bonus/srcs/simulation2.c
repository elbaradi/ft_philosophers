/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   simulation2.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tel-bara <tel-bara@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/20 16:43:12 by tel-bara      #+#    #+#                 */
/*   Updated: 2021/09/20 17:04:48 by tel-bara      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <semaphore.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "proto.h"
#include "structs.h"

static void	kill_processes(t_philo **philos, unsigned long i)
{
	while (i != 0)
	{
		i--;
		kill((*philos)[i].pid, 9);
	}
}

void	end_simulation(t_philo **philos, unsigned long i)
{
	t_specs			*specs;
	pid_t			wait_for_satisfied;

	specs = get_specs();
	if (i != specs->num_philos)
	{
		sem_wait(specs->prompt);
		print_message(PROCESS_ERROR);
		kill_processes(philos, i);
		return ;
	}
	wait_for_satisfied = fork();
	if (wait_for_satisfied == 0)
	{
		while (i > 0)
		{
			i--;
			sem_wait(specs->satisfied);
		}
		exit (0);
	}
	waitpid(-1, 0, 0);
	kill_processes(philos, specs->num_philos);
	kill(wait_for_satisfied, 9);
}

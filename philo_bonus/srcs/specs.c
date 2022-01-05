/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   specs.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tel-bara <tel-bara@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/07 11:29:15 by tel-bara      #+#    #+#                 */
/*   Updated: 2021/09/20 17:03:33 by tel-bara      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <semaphore.h>
#include <unistd.h>
#include "proto.h"
#include "structs.h"

t_specs	*get_specs(void)
{
	static t_specs	specs;

	return (&specs);
}

static void	open_all_sems(void)
{
	t_specs	*specs;
	int		error;

	specs = get_specs();
	error = 0;
	specs->forks = sem_open("philo_forks", \
	O_CREAT | O_EXCL, S_IRWXU, specs->num_philos);
	if (specs->forks == SEM_FAILED)
		error = 1;
	if (!error)
		specs->prompt = sem_open("philo_prompt", \
	O_CREAT | O_EXCL, S_IRWXU, 1);
	if (specs->prompt == SEM_FAILED)
		error = 1;
	if (!error)
		specs->satisfied = sem_open("philo_satisfied", \
	O_CREAT | O_EXCL, S_IRWXU, specs->num_philos);
	if (specs->satisfied == SEM_FAILED)
		error = 1;
	if (!error)
		return ;
	unlink_all_sems();
	write(1, "Failed to initialize semaphores.\n", 33);
	exit (0);
}

void	set_specs(int argc, char **argv)
{
	t_specs	*specs;

	specs = get_specs();
	specs->num_philos = ft_atoi(argv[1]);
	if (specs->num_philos == 0)
		print_message(NO_PHILOS);
	specs->time_to_die = ft_atoi(argv[2]);
	specs->time_to_eat = ft_atoi(argv[3]);
	specs->time_to_sleep = ft_atoi(argv[4]);
	specs->max_meals = 0;
	specs->death = 0;
	if (argc == 6)
		specs->max_meals = ft_atoi(argv[5]);
	if (argc == 6 && specs->max_meals == 0 && argv[5][0] == '0')
		print_message(NO_MEALS);
	unlink_all_sems();
	open_all_sems();
}

void	unlink_all_sems(void)
{
	sem_unlink("philo_prompt");
	sem_unlink("philo_forks");
	sem_unlink("philo_satisfied");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   specs.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tel-bara <tel-bara@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/07 11:29:15 by tel-bara      #+#    #+#                 */
/*   Updated: 2021/09/09 18:50:45 by tel-bara      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include "proto.h"
#include "structs.h"

t_specs	*get_specs(void)
{
	static t_specs	specs;

	return (&specs);
}

void	set_specs(int argc, char **argv)
{
	t_specs	*specs;

	specs = get_specs();
	specs->death = 0;
	specs->satisfied = 0;
	specs->num_philos = ft_atoi(argv[1]);
	if (specs->num_philos == 0)
		print_message(NO_PHILOS);
	specs->time_to_die = ft_atoi(argv[2]);
	specs->time_to_eat = ft_atoi(argv[3]);
	specs->time_to_sleep = ft_atoi(argv[4]);
	specs->max_meals = 0;
	if (argc == 6)
		specs->max_meals = ft_atoi(argv[5]);
	if (argc == 6 && specs->max_meals == 0 && argv[5][0] == '0')
		print_message(NO_MEALS);
	specs->prompt = malloc(sizeof(pthread_mutex_t));
	if (specs->prompt == NULL)
		exit (1);
	pthread_mutex_init(specs->prompt, NULL);
}

void	destroy_specs(void)
{
	t_specs	*specs;

	specs = get_specs();
	pthread_mutex_destroy(specs->prompt);
	free(specs->prompt);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tel-bara <tel-bara@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/29 14:13:04 by tel-bara      #+#    #+#                 */
/*   Updated: 2021/09/09 18:40:50 by tel-bara      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "proto.h"

/* 	PROGRAM SETUP:

	Main
	 |
	 |	[input.c]
	 |	||
	Check input (writes and exits upon error)
	 |
	 |	[specs.c]
	 |	||
	Set specs (store input in the globally accessible struct "t_specs *specs")
	 |
	 |	[forks.c]
	 |	||
	Allocate memory for all forks
	 |
	 |	[timestamp.c]
	 |	||
	Set base timestamp (0 ms benchmark)
	 |
	 |	[simulation.c]
	 |	||
	Allocate memory for all individual philosopher data
	 |
	Spawn all philosophers (pthread_create loop)
				|
	thread: Initialize philosopher data
				|
				|	[death.c]
				|	||
	thread: Create death timer thread for each philosopher
			(Sends a signal to all threads if one philo dies)
				|
				|	[simulation.c]
				|	||
	thread:	Start all routines
				|
				|	[routine.c	prompt.c]
				|	||			||
	thread: Action and prints are protected with a single mutex,
	 |		"pthread_mutex_t *specs->prompt",
	 |		which prevents two actions happening at the exact same time.
	 |		This allows us to reliably suppress prints/actions
	 |		immediately after the simulation has ended.
	 |		(And no issues with a philosopher eating and dying simultaneously.)
	 |
	 |	[simulation.c]
	 |	||
	Wait for all threads to finish (pthread_join loop).
	 |
	 |	[forks.c	specs.c]
	 |	||			||
	Free allocated memory, destroy mutexes.

	TIPS:
	-	Function usleep(ms) tells the system to sleep for at least
		'ms' microseconds. The system, however, might sleep longer than that,
		which affects the simulation. To improve accuracy create
		a better sleep function by calling usleep in a short loop.
	-	If I would rewrite this project I would put the pointers
		to the prompt mutex, to the death signal and to the 
		'number_of_times_each_philosopher_must_eat counter' also
		in all the individual philosopher structs. This would make it more
		straightforward to communicate between philosophers
		that the simulation has ended.
*/

int	main(int argc, char **argv)
{
	input_check(argc, argv);
	set_specs(argc, argv);
	set_forks();
	set_base_timestamp();
	launch_simulation();
	destroy_forks();
	destroy_specs();
	exit (0);
}

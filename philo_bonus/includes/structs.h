/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tel-bara <tel-bara@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/31 14:36:51 by tel-bara      #+#    #+#                 */
/*   Updated: 2021/09/20 13:47:22 by tel-bara      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <semaphore.h>

typedef enum e_input_error
{
	argc_incorrect,
	empty_arg,
	non_numerical,
	phil_too_long,
	time_too_long,
	meals_too_long
}	t_input_error;

typedef enum e_state
{
	thinking,
	grabbing_forks,
	eating,
	sleeping,
	deceased,
	undefined
}	t_state;

typedef struct s_philo
{
	int				index;
	t_state			state;
	unsigned long	last_fed;
	unsigned long	meals;
	pid_t			pid;
}	t_philo;

typedef struct s_specs
{
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	unsigned long	max_meals;
	unsigned long	num_philos;
	int				death;
	sem_t			*satisfied;
	sem_t			*forks;
	sem_t			*prompt;
}	t_specs;

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tel-bara <tel-bara@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/31 14:36:51 by tel-bara      #+#    #+#                 */
/*   Updated: 2021/09/08 16:51:26 by tel-bara      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <pthread.h>

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
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		tid;
}	t_philo;

typedef struct s_specs
{
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	unsigned long	max_meals;
	unsigned long	num_philos;
	unsigned long	satisfied;
	int				death;
	pthread_mutex_t	*prompt;
}	t_specs;

#endif
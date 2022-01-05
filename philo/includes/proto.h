/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   proto.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tel-bara <tel-bara@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/01 12:42:00 by tel-bara      #+#    #+#                 */
/*   Updated: 2021/09/09 19:01:38 by tel-bara      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTO_H
# define PROTO_H

# include <stdlib.h>
# include <pthread.h>
# include "structs.h"

# define HEADER 1
# define FOOTER 2
# define NO_MEALS 3
# define NO_PHILOS 4
# define THREAD_ERROR 5

/* Death */
void			*death_timer(void *ptr);

/* Forks */
pthread_mutex_t	**get_forks(void);
void			set_forks(void);
void			destroy_forks(void);

/* Input */
void			input_check(int argc, char **argv);

/* Prompt */
void			write_prompt(t_state state, unsigned long i,
					unsigned long timestamp);
void			print_message(int option);

/* Routine */
void			eat(t_philo *philo);
void			nap(t_philo *philo);
void			think(t_philo *philo);
void			grab_forks(t_philo *philo);
void			drop_forks(t_philo *philo);

/* Simulation */
void			launch_simulation(void);

/* Specs */
t_specs			*get_specs(void);
void			set_specs(int argc, char **argv);
void			destroy_specs(void);

/* Timestamp */
unsigned long	get_timestamp_in_ms(void);
void			set_base_timestamp(void);

/* Utils */
void			better_usleep(unsigned long sleep_time);
unsigned long	ft_atoi(char *str);
void			*ft_memcpy(void *dst, const void *src, size_t n);
char			*ft_strdup(const char *s, size_t size);
void			nbr_to_string(char *str, unsigned long pos,
					unsigned long nbr, char src);

#endif

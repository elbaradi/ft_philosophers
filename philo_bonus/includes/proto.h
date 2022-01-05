/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   proto.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tel-bara <tel-bara@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/01 12:42:00 by tel-bara      #+#    #+#                 */
/*   Updated: 2021/09/20 16:59:15 by tel-bara      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTO_H
# define PROTO_H

# include <stdlib.h>
# include "structs.h"

# define HEADER 1
# define FOOTER 2
# define NO_MEALS 3
# define NO_PHILOS 4
# define PROCESS_ERROR 5
# define DEATH_CODE 3

/* Death */
void			*death_timer(void *ptr);

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

/* Simulation */
void			launch_simulation(void);
void			end_simulation(t_philo **philos, unsigned long i);

/* Specs */
t_specs			*get_specs(void);
void			set_specs(int argc, char **argv);
void			unlink_all_sems(void);

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

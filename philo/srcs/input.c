/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tel-bara <tel-bara@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/07 09:58:01 by tel-bara      #+#    #+#                 */
/*   Updated: 2021/09/07 12:23:06 by tel-bara      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "structs.h"

static void	input_error(t_input_error error)
{
	if (error == argc_incorrect)
		write(1, "Error. Please provide four or five arguments.\n", 46);
	else if (error == empty_arg)
		write(1, "Error. Please provide non-empty arguments.\n", 43);
	else if (error == non_numerical)
		write(1, \
		"Error. Arguments should all be positive, unpadded numbers.\n", 59);
	else if (error == phil_too_long)
		write(1, \
		"Error. 'number_of_philosophers' should be \
an unpadded number between [0 - 999].\n", 80);
	else if (error == time_too_long)
		write(1, \
		"Error. Don't waste our time: \
'time_to_die', 'time_to_eat' and 'time_to_sleep' \
should be unpadded numbers between [0 - 9999].\n", 122);
	else if (error == meals_too_long)
		write(1, \
		"Error. 'number_of_times_each_philosopher_must_eat' \
should be an unpadded number be between [0 - 99].\n", 98);
	exit(1);
}

void	input_check(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc != 5 && argc != 6)
		input_error(argc_incorrect);
	i = 1;
	while (i != argc)
	{
		j = 0;
		if (argv[i][0] == '\0' && i != 5)
			input_error(empty_arg);
		while (argv[i][j])
		{
			if (i == 5 && j > 1)
				input_error(meals_too_long);
			if (i == 1 && j > 2)
				input_error(phil_too_long);
			if (j > 3)
				input_error(time_too_long);
			if (argv[i][j] < '0' || argv[i][j] > '9')
				input_error(non_numerical);
			j++;
		}
		i++;
	}
}

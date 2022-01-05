/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prompt.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tel-bara <tel-bara@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/02 11:51:59 by tel-bara      #+#    #+#                 */
/*   Updated: 2021/09/20 16:14:56 by tel-bara      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "struct.h"
#include "proto.h"

void	write_prompt(t_state state, unsigned long id, unsigned long timestamp)
{
	t_specs				*specs;
	static const char	*str[] = {
			"| %8ld    %03ld   is thinking.      |\n",
			"| %8ld    %03ld   has taken a fork. |\n",
			"| %8ld    %03ld   is eating.        |\n",
			"| %8ld    %03ld   is sleeping.      |\n",
			"| %8ld    %03ld   died.             |\n",
			NULL
	};

	specs = get_specs();
	if (timestamp > 99999999)
	{
		printf("|%37.0d|\n| Simulation end: time limit reached. |\n", 0);
		exit (DEATH_CODE);
	}
	printf(str[state], timestamp, id);
}

void	print_message(int option)
{
	if (option == NO_MEALS)
	{
		write(1, "\
\nYou sense an air of hostility; your presence is clearly \
disturbing the peace.\nThe Philosophers must have been reading Schopenhauer \
again. Better to leave.\n\n", 157);
		exit (0);
	}
	else if (option == NO_PHILOS)
	{
		write(1, "\
\nHmm... \"Cafeteria closed\". \
Better to come back some other time.\n\n", 66);
		exit (0);
	}
	else if (option == HEADER)
		printf("\
|-------------------------------------|\n\
|    ms    |  id  |                   |\n\
|-------------------------------------|\n");
	else if (option == FOOTER)
		printf("\
|-------------------------------------|\n");
	else if (option == PROCESS_ERROR)
		printf("\
| Failed to create all processes.     |\n");
	return ;
}

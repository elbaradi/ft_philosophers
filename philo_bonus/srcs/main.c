/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tel-bara <tel-bara@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/29 14:13:04 by tel-bara      #+#    #+#                 */
/*   Updated: 2021/09/20 16:12:23 by tel-bara      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "proto.h"

int	main(int argc, char **argv)
{
	input_check(argc, argv);
	set_specs(argc, argv);
	set_base_timestamp();
	launch_simulation();
	unlink_all_sems();
	exit (0);
}

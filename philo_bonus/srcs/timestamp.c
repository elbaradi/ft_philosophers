/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   timestamp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tel-bara <tel-bara@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/01 13:53:57 by tel-bara      #+#    #+#                 */
/*   Updated: 2021/09/20 17:05:59 by tel-bara      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>

static unsigned long	*get_base_timestamp(void)
{
	static unsigned long	base = 0;

	return (&base);
}

void	set_base_timestamp(void)
{
	struct timeval	base_tv;
	unsigned long	*base;

	gettimeofday(&base_tv, NULL);
	base = get_base_timestamp();
	*base = ((1000000 * base_tv.tv_sec + base_tv.tv_usec) / 1000);
}

unsigned long	get_timestamp_in_ms(void)
{
	unsigned long	*base;
	struct timeval	rel;

	base = get_base_timestamp();
	gettimeofday(&rel, NULL);
	return (((1000000 * rel.tv_sec + rel.tv_usec) / 1000) - *base);
}

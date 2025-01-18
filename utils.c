/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:25:07 by nboer             #+#    #+#             */
/*   Updated: 2025/01/18 22:09:02 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	delta_t(long long past, long long cur)
{
	return (cur - past);
}

long long	get_timestamp(void)
{
	struct timeval	time;
	
	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	print_event(long long time, int id, char *str)
	{
		pthread_mutex_lock(&(data->is_printing));
		printf("%ld %i %s\n", time, id, str);
	}
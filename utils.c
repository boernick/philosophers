/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboer <nboer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:25:07 by nboer             #+#    #+#             */
/*   Updated: 2025/01/20 14:06:31 by nboer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	error_handler(char *str, int ret)
{
	ft_put_endl(str, 2);
	return (ret);
}

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

void	print_event(t_data *data, long long time, int id, char *str)
{
	pthread_mutex_lock(&(data->print_lock));
	if (!data->deceased)
		printf("%ld %i %s\n", time, id, str);
	pthread_mutex_unlock(&(data->print_lock));
}

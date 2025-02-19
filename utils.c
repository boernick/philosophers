/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboer <nboer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:25:07 by nboer             #+#    #+#             */
/*   Updated: 2025/02/19 16:18:31 by nboer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

int	error_handler(char *str, int ret)
{
	ft_putendl_fd(str, 2);
	return (ret);
}

long long	d_time(long long past, long long cur)
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
		printf("%lld %i %s\n", time, id, str);
	pthread_mutex_unlock(&(data->print_lock));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboer <nboer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:00:15 by nboer             #+#    #+#             */
/*   Updated: 2025/02/23 14:00:20 by nboer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

// init philosopher struct.
int	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		data->philo[i].id = i;
		data->philo[i].n_eat = 0;
		data->philo[i].fork_left = i;
		data->philo[i].fork_right = (i + 1) % data->n_philos;
		data->philo[i].data = data;
		data->philo[i].last_meal = get_timestamp(data);
		i++;
	}
	return (0);
}

// function to run by every thread, resembling a philo.
void	*philo_thread(void *void_philo)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)void_philo;
	data = philo->data;
	if (philo->id % 2)
		usleep(1000);
	while (!(data->deceased) && !(data->end_meals))
	{
		start_eat(philo, data);
		if (data->deceased || data->end_meals)
			break ;
		start_sleep(philo, data);
		if (data->deceased || data->end_meals)
			break ;
		start_think(philo, data);
		if (data->deceased || data->end_meals)
			break ;
	}
	return (NULL);
}

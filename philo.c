/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboer <nboer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:00:15 by nboer             #+#    #+#             */
/*   Updated: 2025/02/19 16:19:59 by nboer            ###   ########.fr       */
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
		data->philo[i].last_meal = get_timestamp();
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
		usleep(3000);
	if (!data)
		put_error("data is NULL");
	while (!(philo->data->deceased) && !(philo->data->end_meals))
	{
		start_eat(philo, philo->data);
		if (philo->data->end_meals)
			break ;
		start_sleep(philo, philo->data);
		start_think(philo, philo->data);
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 16:29:36 by nick              #+#    #+#             */
/*   Updated: 2025/02/16 16:30:18 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

// print error message.
int	put_error(char *msg)
{
	ft_putendl_fd(msg, STDERR_FILENO);
	return (EXIT_FAILURE);
}

//join threads.
void	join_threads(t_data *data)
{
	int i;
	
	i = 0;
	while (i < data->n_philos)
	{
		printf("end philo [%i]\n", i);
		pthread_join(data->philo[i].id_thread, NULL);
		i++;
	}
}

// init mutex locks for forks and meals.
int	mutex_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		if (pthread_mutex_init(&(data->forks_lock[i]), NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&(data->print_lock), NULL))
		return (1);
	if (pthread_mutex_init(&(data->meal_lock), NULL))
		return (1);
	return (0);
}


// destroy mutex locks.
void	destroy_mutex(t_data *data)
{
	int i = 0;
	while (i < data->n_philos)
	{
		pthread_mutex_destroy(&(data->forks_lock[i]));
		i++;
	}
	pthread_mutex_destroy(&(data->meal_lock));
}
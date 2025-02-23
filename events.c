/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboer <nboer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 18:07:42 by nboer             #+#    #+#             */
/*   Updated: 2025/02/23 14:08:15 by nboer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

void	do_event(long long time, t_data *rules)
{
	long long	t_start;
	long long	t_now;

	t_start = get_timestamp(rules);
	while (!rules->deceased)
	{
		t_now = get_timestamp(rules);
		if (d_time(t_start, t_now) >= time)
			break ;
		usleep(50);
	}
}

void	start_eat(t_philo *philo, t_data *r)
{
	pthread_mutex_lock(&(r->forks_lock[philo->fork_left]));
	print_event(r, get_timestamp(r), philo->id, "has taken a left fork");
	pthread_mutex_lock(&(r->forks_lock[philo->fork_right]));
	print_event(r, get_timestamp(r), philo->id, "has taken a right fork");
	pthread_mutex_lock(&(r->meal_lock));
	print_event(r, get_timestamp(r), philo->id, "is eating");
	philo->last_meal = get_timestamp(r);
	pthread_mutex_unlock(&(r->meal_lock));
	(philo->n_eat)++;
	do_event(r->t_eat, r);
	pthread_mutex_unlock(&(r->forks_lock[philo->fork_left]));
	pthread_mutex_unlock(&(r->forks_lock[philo->fork_right]));
}

void	start_sleep(t_philo *philo, t_data *rules)
{
	print_event(rules, get_timestamp(rules), philo->id, "is sleeping");
	do_event(rules->t_sleep, rules);
}

void	start_think(t_philo *philo, t_data *rules)
{
	print_event(rules, get_timestamp(rules), philo->id, "is thinking");
}

void	check_deceased(t_philo *philo, t_data *data)
{
	long	now;

	now = get_timestamp(data);
	if (d_time(philo->last_meal, now) > data->t_death)
	{
		pthread_mutex_lock(&(data->meal_lock));
		print_event(data, now - 1, philo->id, "died");
		data->deceased = 1;
		pthread_mutex_unlock(&(data->meal_lock));
	}
}

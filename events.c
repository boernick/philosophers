/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboer <nboer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 18:07:42 by nboer             #+#    #+#             */
/*   Updated: 2025/02/27 14:53:36 by nboer            ###   ########.fr       */
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
		usleep(100);
	}
}

void	start_eat(t_philo *philo, t_data *r)
{
	pthread_mutex_lock(&(r->forks_lock[philo->fork_left]));
	print_event(r, get_timestamp(r), philo->id, "has taken a left fork");
	pthread_mutex_lock(&(r->forks_lock[philo->fork_right]));
	print_event(r, get_timestamp(r), philo->id, "has taken a right fork");
	print_event(r, get_timestamp(r), philo->id, "is eating");
	pthread_mutex_lock(&(r->meal_lock[philo->id]));
	philo->last_meal = get_timestamp(r);
	(philo->n_eat)++;
	pthread_mutex_unlock(&(r->meal_lock[philo->id]));
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
	pthread_mutex_lock(&(data->meal_lock[philo->id]));
	if (d_time(philo->last_meal, now) > data->t_death)
	{
		print_event(data, now, philo->id, "died");
		data->deceased = 1;
	}
	pthread_mutex_unlock(&(data->meal_lock[philo->id]));
}

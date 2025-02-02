/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboer <nboer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 18:07:42 by nboer             #+#    #+#             */
/*   Updated: 2025/02/02 18:09:57 by nboer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

void do_event(long long time, t_data *rules)
{
	long long	t_start;

	t_start = get_timestamp();
	while (!rules->deceased)
	{
		if (d_time(t_start, get_timestamp()) >= time)
			break;
		usleep(100);
	}
}

void	start_eat(t_philo *philo, t_data *rules)
{
	pthread_mutex_lock(&(rules->forks_lock[philo->fork_left]));
	print_event(rules, get_timestamp(), philo->id, "has taken a fork");
	pthread_mutex_lock(&(rules->forks_lock[philo->fork_right]));
	print_event(rules, get_timestamp(), philo->id, "has taken a fork");
	pthread_mutex_lock(&(rules->meal_lock));
	print_event(rules, get_timestamp(), philo->id, "is eating");
	philo->last_meal = get_timestamp();
	(philo->n_eat)++;
	pthread_mutex_unlock(&(rules->meal_lock));
	do_event(rules->t_eat, rules);
	pthread_mutex_unlock(&(rules->forks_lock[philo->fork_left]));
	pthread_mutex_unlock(&(rules->forks_lock[philo->fork_right]));
}

void	start_sleep(t_philo *philo, t_data *rules)
{
	print_event(rules, get_timestamp(), philo->id, "is sleeping");
	do_event(rules->t_sleep, rules);
}

void	start_think(t_philo *philo, t_data *rules)
{
	print_event(rules, get_timestamp(), philo->id, "is thinking");
}

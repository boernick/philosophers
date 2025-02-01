/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboer <nboer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:26:16 by nboer             #+#    #+#             */
/*   Updated: 2025/02/01 19:02:42 by nboer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	put_error(char *msg)
{
	ft_putendl_fd(msg, STDERR_FILENO);
	return (EXIT_FAILURE);
}

int	init_philos(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		philo[i].id = i;
		philo[i].t_death = data->t_death; //maybe not right.
		philo[i].t_sleep = 0; //fout
		philo[i].t_eat = 0; //fout
		philo[i].n_eat = 0;
		philo[i].fork_left = i;
		philo[i].fork_right = (i + 1) % data->n_philos;
		philo[i].data = data;
		i++;
	}
	return (0);
}
void do_event(long long time, t_data *rules)
{
	long long	t_start;

	t_start = get_timestamp();
	while (!rules->deceased)
	{
		if (delta_time(t_start, get_timestamp()) >= time)
			break;
		usleep(100);
	}
}

void	start_eat(t_philo *philo, t_data *rules)
{
	pthread_mutex_lock(&(rules->forks_lock[philo->fork_left]));
	print_event(&rules, get_timestamp(), philo->id, "has taken a fork");
	pthread_mutex_lock(&(rules->forks_lock[philo->fork_right]));
	print_event(&rules, get_timestamp(), philo->id, "has taken a fork");
	pthread_mutex_lock(&(rules->meal_lock));
	print_event(&rules, get_timestamp(), philo->id, "is eating");
	philo->last_meal = get_timestamp();
	(philo->n_eat)++;
	pthread_mutex_unlock(&(rules->meal_lock));
	do_event(rules->t_eat, rules);
	pthread_mutex_unlock(&(rules->forks_lock[philo->fork_left]));
	pthread_mutex_unlock(&(rules->forks_lock[philo->fork_right]));
}

void	start_sleep(t_philo *philo, t_data *rules)
{
	print_event(&rules, get_timestamp(), philo->id, "is sleeping");
	do_event(rules->t_sleep, rules);
}

void	start_think(t_philo *philo, t_data *rules)
{
	print_event(&rules, get_timestamp(), philo->id, "is thinking");
}

void	*philo_thread(void *void_philo) // function that runs when thread is created
{
	t_philo	*philo;
	
	philo = (t_philo *)void_philo;
	while (!(philo->data->deceased))
	{
		start_think(philo, philo->data);
		start_eat(philo, philo->data); // after eating event, add lock
			if (philo->data->end_meals)
				break;
		start_sleep(philo, philo->data);
	}
}

void	launch_diner(t_philo *philo, t_data *data)
{
	int i;
	int ret;
	
	data->diner_start = get_timestamp();
	i = 0;
	ret = 0;
	while (i < data->n_philos)
	{
		ret = pthread_create(&(data->philo[i].id_thread), NULL, philo_thread, &(data->philo[i]));
		if (ret)
			return (error_handler("error creating thread", ret));
		i++;
	}
}

int	mutex_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		pthread_mutex_init(&(data->forks_lock[i]), NULL);
		i++;
	}
	if (pthread_mutex_init(&(data->print_lock), NULL))
		return (1);
	if (pthread_mutex_init(&(data->meal_lock), NULL))
		return (1);
	return (0);
}

int prepare_diner(t_data *rules, t_philo *philo, char **argv)
{
	set_rules(rules, argv);
	if (wrong_input(rules, argv))
		return (put_error("wrong input"));
	if (mutex_init(&rules))
		return (put_error("mutex init failed"));
	init_philos(&rules, &philo);
	return (0);
}

int	wrong_input(t_data *rules, char **argv)
{
	if (rules->n_philos <= 1 || rules->n_philos > 100 || rules->t_eat < 0 
		|| rules->t_sleep < 0 || rules->t_death < 0)
		return (1);
	if (argv[5])
	{
		if (rules->n_meals < 1)
			return (1);
	}
}

void	set_rules(t_data *rules, char **argv)
{
	rules->n_philos = ft_atoi(argv[1]);
	rules->t_death = ft_atoi(argv[2]);
	rules->t_eat = ft_atoi(argv[3]);
	rules->t_sleep = ft_atoi(argv[4]);
	rules->philos_dead = 0;
	rules->n_philos_fed = 0;
	if (argv[5])
		rules->n_meals = ft_atoi(argv[5]);
	else 
		rules->n_meals = -1;
}

void	check_diner_end(t_data *rules, )
{
	int i;
	while (!(rules->deceased))
	i = 0;
	while (i < rules->n_philos)
	{
		
	}
}

int	main(int argc, char **argv)
{
	t_data	rules;
	t_philo	philo;

	set_rules(&rules, argv);
	if (argc != 5 && argc != 6)
		return (put_error("Error: wrong argument count"));
	prepare_diner(&rules, &philo, argv);
	launch_diner(&philo, &rules);
	check_diner_end(&rules);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboer <nboer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:26:16 by nboer             #+#    #+#             */
/*   Updated: 2025/02/09 17:09:46 by nboer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

int	put_error(char *msg)
{
	ft_putendl_fd(msg, STDERR_FILENO);
	return (EXIT_FAILURE);
}

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

void	*philo_thread(void *void_philo) // function that runs when thread is created
{
	t_philo	*philo;
	t_data	*data;
	
	philo = (t_philo *)void_philo;
	data = philo->data;
	if (philo->id % 2)
		usleep(10000);
	if (!data)
		put_error("data is NULL");
	printf("%lli timestamp in philothread for last meal\n", philo->last_meal);
	while (!(philo->data->deceased))
	{
		start_eat(philo, philo->data); // after eating event, add lock
			if (philo->data->end_meals)
				break;
		start_sleep(philo, philo->data);
		start_think(philo, philo->data);
	}
	return (NULL);
}

int	launch_diner(t_data *data)
{
	int i;
	int ret;
	
	data->diner_start = get_timestamp();
	i = 0;
	ret = 0;
	while (i < data->n_philos)
	{
		printf("philo %i last meal time stamp = %lli\n", i, data->philo[i].last_meal); //debug
		ret = pthread_create(&(data->philo[i].id_thread), NULL, philo_thread, &(data->philo[i]));
		if (ret)
			return (error_handler("error creating thread", ret));
		i++;
	}
	return (ret);
}

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

int prepare_diner(t_data *rules, char **argv)
{
	set_rules(rules, argv);
	if (wrong_input(rules, argv))
		return (put_error("wrong input"));
	if (mutex_init(rules))
		return (put_error("mutex init failed"));
	init_philos(rules);
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
	return (0);
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

void	check_diner_end(t_data *data)
{
	int	i;

	while (!(data->end_meals))
	{
		i = 0;
		while(i < data->n_philos && !(data->deceased))
		{
			check_deceased(&(data->philo[i]), data);
			usleep(100);
			i++;
		}
		if (data->deceased)
			break;
		i = 0;
		while(data->philo[i].n_eat >= data->n_meals && data->n_meals != -1)
		{
			if (i == data->n_philos)
			{
				data->end_meals = 1;
				return;
			}
			i++;
		}
	}
}

int	main(int argc, char **argv)
{
	t_data	rules;
	int ret;
	
	ret = 0;
	if (argc != 5 && argc != 6)
		return (put_error("Error: wrong argument count"));
	prepare_diner(&rules, argv);
	ret = launch_diner(&rules);
	check_diner_end(&rules);
}

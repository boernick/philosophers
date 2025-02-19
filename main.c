/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboer <nboer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:26:16 by nboer             #+#    #+#             */
/*   Updated: 2025/02/19 13:27:08 by nboer            ###   ########.fr       */
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
	printf("%lli timestamp in philothread for last meal\n", philo->last_meal);
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

// create thread for each philosopher.
int	launch_diner(t_data *data)
{
	int	i;
	int	ret;

	data->diner_start = get_timestamp();
	i = 0;
	ret = 0;
	while (i < data->n_philos)
	{
		ret = pthread_create(&(data->philo[i].id_thread), 
				NULL, philo_thread, &(data->philo[i]));
		if (ret)
			return (error_handler("error creating thread", ret));
		i++;
	}
	return (ret);
}

// initiates structs and error checks.
int	prepare_diner(t_data *rules, char **argv)
{
	set_rules(rules, argv);
	if (wrong_input(rules, argv))
		return (put_error("wrong input"));
	if (mutex_init(rules))
		return (put_error("mutex init failed"));
	init_philos(rules);
	return (0);
}

// check for input errors.
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

// init rules from arguments given by user.
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

// checks if a philo died or if all philos have eaten n_meals.
void	check_diner_end(t_data *data)
{
	int	i;

	while (!(data->end_meals))
	{
		i = 0;
		while (i < data->n_philos && !(data->deceased))
		{
			check_deceased(&(data->philo[i]), data);
			usleep(100);
			i++;
		}
		if (data->deceased)
			break ;
		i = 0;
		while (data->philo[i].n_eat >= data->n_meals && data->n_meals != -1)
		{
			if (i == data->n_philos - 1)
			{
				data->end_meals = 1;
				return ;
			}
			i++;
		}
	}
}

int	main(int argc, char **argv)
{
	t_data	rules;
	int		ret;

	ret = 0;
	if (argc != 5 && argc != 6)
		return (put_error("Error: wrong argument count"));
	prepare_diner(&rules, argv);
	ret = launch_diner(&rules);
	check_diner_end(&rules);
	join_threads(&rules);
	destroy_mutex(&rules);
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboer <nboer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:26:16 by nboer             #+#    #+#             */
/*   Updated: 2025/02/23 14:08:45 by nboer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

// create thread for each philosopher.
int	launch_diner(t_data *data)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	data->diner_start = get_timestamp(data);
	if (data->n_philos == 1)
	{
		print_event(data, get_timestamp(data), 0, "died");
		ret = 1;
	}
	if (!ret)
	{
		while (i < data->n_philos)
		{
			ret = pthread_create(&(data->philo[i].id_thread), 
					NULL, philo_thread, &(data->philo[i]));
			if (ret)
				return (error_handler("error creating thread", ret));
			i++;
		}
	}
	return (ret);
}

// initiates structs and error checks.
int	prepare_diner(t_data *rules, char **argv)
{
	int	ret;

	ret = 0;
	set_rules(rules, argv);
	ret = wrong_input(rules, argv);
	if (ret)
	{
		ft_printf("Args: n_philos, t_die, t_eat, t_sleep, n_meals\n");
		return (put_error("Error: wrong input"));
	}
	if (!ret && mutex_init(rules))
		ret = put_error("mutex init failed");
	if (!ret)
		init_philos(rules);
	return (ret);
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
		i = -1;
		while (++i < data->n_philos && !(data->deceased))
			check_deceased(&(data->philo[i]), data);
		if (data->deceased)
			return ;
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
		usleep(1000);
	}
}

int	main(int argc, char **argv)
{
	t_data	rules;
	int		ret;

	ret = 0;
	if (argc != 5 && argc != 6)
	{
		ft_printf("Args: n_philos, t_die, t_eat, t_sleep, n_meals\n");
		return (put_error("Error: wrong input"));
	}
	ret = prepare_diner(&rules, argv);
	if (!ret)
		ret = launch_diner(&rules);
	if (!ret)
	{
		check_diner_end(&rules);
		join_threads(&rules);
		destroy_mutex(&rules);
	}
	return (ret);
}

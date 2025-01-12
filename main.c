/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboer <nboer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:26:16 by nboer             #+#    #+#             */
/*   Updated: 2025/01/12 18:42:44 by nboer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_philos(t_rules *rules)
{
	int	i;
	
	i = 0;
	while (i < rules->philos_n)
	{
		philos[i].time_death = i;
		philos[i].time_sleep = 0;
		philos[i].time_eat = 0;
		i++;
	}
}

void	start_eating(t_philo *philo)
{
	
}

void	set_rules(t_rules *rules, char **argv)
{
	rules->philos_n = ft_atoi(argv[1]);
	rules->time_death = ft_atoi(argv[2]);
	rules->time_eat = ft_atoi(argv[3]);
	rules->time_sleep = ft_atoi(argv[4]);
	rules->philos_dead = 0;
}

int	main(int argc, char **argv)
{
	t_rules rules;
	
	set_rules(&rules, argv);
	if (argc != 5 && argc != 6)
	{
		ft_putendl_fd("Error: wrong argument count", STDERR_FILENO);
		return (1);
	}
	//init_philos(rules);
	//init_diner;
}

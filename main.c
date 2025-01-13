/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:26:16 by nboer             #+#    #+#             */
/*   Updated: 2025/01/13 23:01:33 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	put_error(char *msg)
{
	ft_putendl_fd(msg, STDERR_FILENO);
	return (EXIT_FAILURE);
}

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

int init_diner(t_rules *rules, char **argv)
{
	set_rules(rules, argv);
	if (check_input(rules) == 1)
		return (put_error("wrong input"));
	

}

int	check_input(t_rules *rules, char **argv))
{
	if (rules->philos_n <= 1 || rules->philos_n > 100 || rules->t_eat < 0 
		|| rules->t_sleep < 0 || rules->t_death < 0)
		return (EXIT_FAILURE);
	
	
}

void	set_rules(t_rules *rules, char **argv)
{
	rules->philos_n = ft_atoi(argv[1]);
	rules->t_death = ft_atoi(argv[2]);
	rules->t_eat = ft_atoi(argv[3]);
	rules->t_sleep = ft_atoi(argv[4]);
	rules->philos_dead = 0;
	rules->philos_fed = 0;
	if (argv[5])
	{
		rules->n_meals = ft_atoi(argv[5]);
	}
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

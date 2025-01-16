/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboer <nboer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:26:16 by nboer             #+#    #+#             */
/*   Updated: 2025/01/16 16:31:43 by nboer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	put_error(char *msg)
{
	ft_putendl_fd(msg, STDERR_FILENO);
	return (EXIT_FAILURE);
}

int	init_philos(t_rules *rules, t_philo *philo)
{
	int	i;
	
	i = 0;
	while (i < rules->philos_n)
	{
		philo[i].t_death = i;
		philo[i].t_sleep = 0;
		philo[i].t_eat = 0;
		i++;
	}
}

void	start_eating(t_philo *philo)
{
	
}

int init_diner(t_rules *rules, char **argv)
{
	set_rules(rules, argv);
	if (wrong_input(rules, argv))
		return (put_error("wrong input"));
	

}

int	wrong_input(t_rules *rules, char **argv)
{
	if (rules->philos_n <= 1 || rules->philos_n > 100 || rules->t_eat < 0 
		|| rules->t_sleep < 0 || rules->t_death < 0)
		return (EXIT_FAILURE);
	if (argv[5])
	{
		if (rules->n_meals < 1)
			return (EXIT_FAILURE);
	}
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
		rules->n_meals = ft_atoi(argv[5]);
	else 
		rules->n_meals = -1;
}

int	main(int argc, char **argv)
{
	t_rules rules;
	t_philo philo;
	
	set_rules(&rules, argv);
	if (argc != 5 && argc != 6)
		return (put_error("Error: wrong argument count"));
	init_philos(&rules, &philo);
	//init_diner;
}

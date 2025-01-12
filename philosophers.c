/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 20:57:53 by nick              #+#    #+#             */
/*   Updated: 2025/01/12 11:28:16 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	int	number_of_philosophers = argv[1];
	int time_to_die = ft_atoi(argv[2]);
	int	time_to_eat = argv[3];
	int	time_to_sleep = argv[4];

	if (argc != 5 && argc != 6)
	{
		
	}

	int i = 0;
	while (i < number_of_philosophers)
		//create_philosopher(i);
	
	
}
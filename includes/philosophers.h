#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <sys/time.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include "../includes/Libft/libft.h"
#include "../includes/ft_printf/ft_printf.h"

#define SLEEP 0
#define EAT 1
#define DEAD 2

typedef struct	s_philo
{
	int id;
	int	status;
	int t_death;
	int t_eat;
	int	t_sleep;
	int n_eat;
	int	is_dead;
} t_philo;

typedef struct	s_rules
{
	int	philos_n;
	int philos_dead;
	int philos_fed;
	int t_death;
	int	t_eat;
	int	t_sleep;
	int	n_meals;
} t_rules;

#endif

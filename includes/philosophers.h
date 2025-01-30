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

typedef struct	s_philo
{
	int id;
	int t_death;
	int t_eat;
	int	t_sleep;
	int n_eat;
	int fork_left;
	int fork_right;
	pthread_t	id_treath;
} t_philo;

typedef struct	s_data
{
	t_philo philo[200];
	int	philos_n;
	int philos_dead;
	int philos_fed;	
	int t_death;
	int	t_eat;
	int	t_sleep;
	int	n_meals;
	int deceased;
	pthread_mutex_t print_lock;
	pthread_mutex_t forks_lock[250];
	pthread_mutex_t meal_lock;
} t_data;

#endif

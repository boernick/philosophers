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
	int			id;
	int			t_death;
	int			t_eat;
	int			t_sleep;
	int			n_eat;
	int			fork_left;
	int			fork_right;
	long long	last_meal;
	pthread_t	id_thread;
	t_data		*data;
} t_philo;

typedef struct	s_data
{
	t_philo			philo[250];
	int				n_philos; // amount of philosophers
	int 			philos_dead; // 
	int 			n_philos_fed;	
	int 			t_death; // user input: time till die
	int				t_eat; // user input: time how long it takes to eat
	int				t_sleep; // user input: time a philosopher will spend sleeping
	int				n_meals; // user input: amoutn of times all philosophers must eat before simulation ends. if not specified, then continue untill deceased.
	int 			deceased; // 0 standard, if 1 then philo died;
	int				end_meals; // 0 standard, 1 if all philosophers had n_meals.
	long long		diner_start;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	forks_lock[250];
	pthread_mutex_t	meal_lock;
} t_data;

void		print_event(t_data *data, long long time, int id, char *str);
long long	delta_time(long long past, long long cur);
long long	get_timestamp(void);
int			error_handler(char *str, int ret);
int			put_error(char *msg);
int			init_philos(t_data *data, t_philo *philo);


#endif

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

struct s_data;

typedef struct	s_philo
{
	int					id;
	int					n_eat;
	int					fork_left;
	int					fork_right;
	long long			last_meal;
	pthread_t			id_thread;
	struct s_data		*data;
} t_philo;

typedef struct	s_data
{
	t_philo			philo[250];
	int				n_philos;
	int 			philos_dead;
	int 			n_philos_fed;	
	int 			t_death;
	int				t_eat;
	int				t_sleep;
	int				n_meals;
	int 			deceased;
	int				end_meals;
	long long		diner_start;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	forks_lock[250];
	pthread_mutex_t	meal_lock;
} t_data;

int			put_error(char *msg);
int			init_philos(t_data *data);
void		do_event(long long time, t_data *rules);
void		start_eat(t_philo *philo, t_data *rules);
void		start_sleep(t_philo *philo, t_data *rules);
void		start_think(t_philo *philo, t_data *rules);
int			launch_diner(t_data *data);
int			mutex_init(t_data *data);
int			prepare_diner(t_data *rules, char **argv);
int			wrong_input(t_data *rules, char **argv);
void		set_rules(t_data *rules, char **argv);
void		check_diner_end(t_data *data);
int			error_handler(char *str, int ret);
long long	d_time(long long past, long long cur);
long long	get_timestamp(void);
void		print_event(t_data *data, long long time, int id, char *str);
void		check_deceased(t_philo *philo, t_data *rules);
void		join_threads(t_data *data);
void		destroy_mutex(t_data *data);

#endif

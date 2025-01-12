#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdlib.h>
#include <unistd.h>

#define SLEEP 0
#define EAT 1
#define DEAD 2

typedef struct	s_philo
{
	int	status;
} t_philo;


#endif
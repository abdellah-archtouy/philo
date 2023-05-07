#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_sah
{
	pthread_mutex_t	*fork;
	pthread_mutex_t	*tstart;
	int				nphilo;
	int				time_of_die;
	int				time_of_eat;
	int				time_of_sleap;
	long			start;
	long			time;
	int				index;
	int				paus;
}		t_sah;

typedef struct s_philo
{
	int				id;
	long			last_eat;
	int				n_of_meal;
	pthread_mutex_t	my_mutex;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	t_sah			*sah;
}			t_philo;

void	*tasks(void *ptr);
long	ft_get_time(void);
int		ft_atoi(const char *str);
int		ft_is_die(long time, t_philo *ph);
t_sah	*get_arg(t_sah *sah, char **av, int ac);
void	ft_int_ph(t_sah *ph, char **av);
t_philo	*init_data(t_philo *ph, t_sah	*sah, int ac, char **av);

#endif
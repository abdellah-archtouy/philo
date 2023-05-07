#include "philo.h"

int	check_die(long time, long l, t_philo	*ph, int i)
{
	(void)i;
	pthread_mutex_lock(ph->sah->tstart);
	if (l - time > ph->sah->time_of_die && ph->sah->paus != 1)
	{
		ph->sah->paus = 1;
		ph->sah->index = ph->id;
		pthread_mutex_unlock(ph->sah->tstart);
		pthread_mutex_unlock(ph->right_fork);
		pthread_mutex_unlock(ph->left_fork);
		return (1);
	}
	pthread_mutex_unlock(ph->sah->tstart);
	if (ph->sah->paus == 1)
	{
		pthread_mutex_unlock(ph->right_fork);
		pthread_mutex_unlock(ph->left_fork);
		return (1);
	}
	return (0);
}

int	ft_usleep(long time, t_philo *ph)
{
	long start = ft_get_time();

	(void)ph;
	while (ft_get_time() - start < time)
	{	
		// if (check_die(time, ft_get_time() - ph->sah->start, ph, 1) == 1)
		// 	return (1);
		usleep(100);
	}
	return (0);
}

void	handel(t_philo *ph)
{
	pthread_mutex_lock(ph->right_fork);
	printf("%ld %d has taken a fork\n", ft_get_time() - ph->sah->start, ph->id);
	ph->sah->index = ph->id;
	ph->sah->paus = 1;
}

void	*tasks(void *ptr)
{
	t_philo	*ph;

	ph = (t_philo *)ptr;
	if ((ph->id % 2) == 0)
		usleep(150);
	if (ph->sah->nphilo == 1)
		return (handel(ph), NULL);
	else
	{
		while (ph->n_of_meal--)
		{
			pthread_mutex_lock(ph->right_fork);
			printf("%ld %d has taken a fork\n", ft_get_time() - ph->sah->start, ph->id);
			pthread_mutex_lock(ph->left_fork);
			printf("%ld %d has taken a fork\n", ft_get_time() - ph->sah->start, ph->id);
			printf("%ld %d is eating\n", ft_get_time() - ph->sah->start, ph->id);
			if(ft_is_die(ph->sah->time_of_eat, ph) == 1)
				break ;
			ph->last_eat = ft_get_time() - ph->sah->start;
			pthread_mutex_unlock(ph->right_fork);
			pthread_mutex_unlock(ph->left_fork);
			printf("%ld %d is sleeping\n", ft_get_time() - ph->sah->start, ph->id);
			if(ft_is_die(ph->sah->time_of_sleap, ph) == 1)
				break ;
			printf("%ld %d is thinking\n", ft_get_time() - ph->sah->start, ph->id);
		}
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	int			i = 0;
	t_philo		*ph;
	t_sah		*sah;
	pthread_t	*philo;

	if (ac >= 5 && ac <= 6)
	{
		sah = malloc(sizeof(t_sah));
		sah = get_arg(sah, av, ac);
		if (!sah)
			return (printf("error\n"), 1);
		ph = malloc(sizeof(t_philo) * sah->nphilo);
		ph = init_data(ph, sah, ac, av);
		if (!ph)
			return (printf("error\n"), 1);
		philo = malloc(sizeof(pthread_t) * sah->nphilo);
		if (philo == NULL)
			return (0);
		while (i < sah->nphilo)
		{
			if (pthread_create(&philo[i], NULL, &tasks, &ph[i]) != 0)
				break ;
			i++;
		}
		i = 0;
		while (i < sah->nphilo)
		{
			if (pthread_join(philo[i], NULL) != 0)
				break ;
			i++;
		}
		i = 0;
		if (ph->sah->paus == 1)
			printf("%ld %d is died \n",
				ft_get_time() - ph->sah->start, ph->sah->index);
		pthread_mutex_destroy(ph->left_fork);
		pthread_mutex_destroy(ph->right_fork);
		pthread_mutex_destroy(ph->sah->tstart);
	}
	return (0);
}

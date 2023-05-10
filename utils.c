#include "philo.h"

long	ft_atoi(const char *str)
{
	int		i;
	int		b;
	long	r;

	i = 0;
	r = 0;
	b = 1;
	while (str[i] == '\n' || str[i] == '\t' || str[i] == ' '
		|| str[i] == '\r' || str[i] == '\f' || str[i] == '\v')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			b = b * (-1);
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		r = r * 10 + (str[i] - '0');
		i++;
	}
	return (r * b);
}

void	ft_int_ph(t_sah *ph, char **av)
{
	ph->paus = 0;
	ph->nphilo = ft_atoi(av[1]);
	ph->time_of_die = ft_atoi(av[2]);
	ph->time_of_eat = ft_atoi(av[3]);
	ph->time_of_sleap = ft_atoi(av[4]);
	ph->start = ft_get_time();
}

t_sah	*get_arg(t_sah *sah, char **av, int ac)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	if (ft_check_max(ac, av) == 1)
		return (NULL);
	while (j < ac)
	{
		i = 0;
		if (av[j][i] == '+')
			i++;
		if (av[j][i] == '-' || av[j][i] == '\0')
			return (NULL);
		while (av[j][i])
		{
			if (av[j][i] < '0' || av[j][i] > '9')
				return (NULL);
			i++;
		}
		j++;
	}
	ft_int_ph(sah, av);
	return (sah);
}

t_philo	*init_data(t_philo *ph, t_sah	*sah, int ac, char **av)
{
	int		i;

	i = 0;
	sah->fork = malloc(sizeof(pthread_mutex_t) * sah->nphilo);
	if (!sah->fork)
		return (NULL);
	while (i < sah->nphilo)
	{
		ph[i].sah = sah;
		ph[i].right_fork = &(sah->fork[i]);
		if (i == (sah->nphilo - 1))
			ph[i].left_fork = &(sah->fork[0]);
		else
			ph[i].left_fork = &(sah->fork[i + 1]);
		ph[i].id = i + 1;
		if (ac == 6)
			ph[i].n_of_meal = ft_atoi(av[5]);
		else
			ph[i].n_of_meal = -1;
		pthread_mutex_init(&sah->fork[i], NULL);
		i++;
	}
	ph->sah->tstart = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(ph->sah->tstart, NULL);
	return (ph);
}

long	ft_get_time(void)
{
	long			time;
	struct timeval	real_time;

	gettimeofday(&real_time, NULL);
	time = (real_time.tv_sec * 1000) + (real_time.tv_usec / 1000);
	return (time);
}

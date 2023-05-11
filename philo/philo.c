/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchtou <aarchtou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 09:44:32 by aarchtou          #+#    #+#             */
/*   Updated: 2023/05/11 15:47:20 by aarchtou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	*ft_handel2(t_philo *ph)
{
	while (ph->n_of_meal--)
	{
		pthread_mutex_lock(ph->right_fork);
		printf("%ld %d has taken a fork\n",
			ft_get_time() - ph->sah->start, ph->id);
		pthread_mutex_lock(ph->left_fork);
		printf("%ld %d has taken a fork\n",
			ft_get_time() - ph->sah->start, ph->id);
		printf("%ld %d is eating\n", ft_get_time() - ph->sah->start, ph->id);
		if (ft_is_die(ph->sah->time_of_eat, ph) == 1)
			break ;
		ph->last_eat = ft_get_time() - ph->sah->start;
		pthread_mutex_unlock(ph->right_fork);
		pthread_mutex_unlock(ph->left_fork);
		printf("%ld %d is sleeping\n", ft_get_time() - ph->sah->start, ph->id);
		if (ft_is_die(ph->sah->time_of_sleap, ph) == 1)
			break ;
		printf("%ld %d is thinking\n", ft_get_time() - ph->sah->start, ph->id);
	}
	return (NULL);
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
		ft_handel2(ph);
	}
	return (NULL);
}

void	ft_creat_thread(t_philo *ph, pthread_t *philo, t_sah *sah)
{
	int	i;

	i = 0;
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
	if (ph->sah->paus == 1)
		printf("%ld %d is died \n",
			ft_get_time() - ph->sah->start, ph->sah->index);
	return ;
}

int	main(int ac, char **av)
{
	t_philo		*ph;
	t_sah		*sah;
	pthread_t	*philo;

	if (ac >= 5 && ac <= 6)
	{
		sah = malloc(sizeof(t_sah));
		if (!sah)
			return (printf("error\n"), 1);
		sah = get_arg(sah, av, ac);
		if (!sah)
			return (printf("error\n"), 1);
		ph = malloc(sizeof(t_philo) * sah->nphilo);
		if (!ph)
			return (free(sah), printf("error\n"), 1);
		ph = init_data(ph, sah, ac, av);
		philo = malloc(sizeof(pthread_t) * sah->nphilo);
		if (!philo)
			return (ft_free2(ph, philo), 0);
		ft_creat_thread(ph, philo, sah);
		ft_free2(ph, philo);
	}
	else
		printf("error\n");
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchtou <aarchtou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 09:44:44 by aarchtou          #+#    #+#             */
/*   Updated: 2023/05/11 15:37:10 by aarchtou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_unlock_fork(t_philo *ph)
{
	pthread_mutex_unlock(ph->right_fork);
	pthread_mutex_unlock(ph->left_fork);
}

int	ft_is_die(long time, t_philo *ph)
{
	long	x;

	x = ft_get_time();
	while (time > (ft_get_time() - x))
	{
		pthread_mutex_lock(ph->sah->tstart);
		if ((ft_get_time() - ph->sah->start - ph->last_eat)
			>= ph->sah->time_of_die
			&& ph->sah->paus == 0)
		{
			ph->sah->index = ph->id;
			ph->sah->time = ft_get_time() - ph->sah->start;
			ph->sah->paus = 1;
			pthread_mutex_unlock(ph->sah->tstart);
			return (ft_unlock_fork(ph), 1);
		}
		pthread_mutex_unlock(ph->sah->tstart);
		pthread_mutex_lock(ph->sah->tstart);
		if (ph->sah->paus == 1)
			return (pthread_mutex_unlock(ph->sah->tstart),
				ft_unlock_fork(ph), 1);
		pthread_mutex_unlock(ph->sah->tstart);
		usleep(100);
	}
	return (0);
}

void	ft_free2(t_philo *ph, pthread_t *philo)
{
	if (philo)
		free(philo);
	free(ph->sah->tstart);
	free(ph->sah->fork);
	free(ph->sah);
	free(ph);
}

void	handel(t_philo *ph)
{
	pthread_mutex_lock(ph->right_fork);
	printf("%ld %d has taken a fork\n", ft_get_time() - ph->sah->start, ph->id);
	while (1)
	{
		if (ft_get_time() - ph->sah->start > ph->sah->time_of_die)
		{
			ph->sah->index = ph->id;
			ph->sah->time = ft_get_time() - ph->sah->start;
			ph->sah->paus = 1;
			break ;
		}
	}
}

int	ft_check_max(int ac, char **av)
{
	if (ft_atoi(av[1]) > 200 || ft_atoi(av[2]) > 2147483647
		|| ft_atoi(av[3]) > 2147483647 || ft_atoi(av[4]) > 2147483647
		|| (ac == 6 && ft_atoi(av[5]) > 2147483647))
		return (1);
	else if (ft_atoi(av[1]) < 1 || ft_atoi(av[2]) < 60
		|| ft_atoi(av[3]) < 60 || ft_atoi(av[4]) < 60)
		return (1);
	return (0);
}

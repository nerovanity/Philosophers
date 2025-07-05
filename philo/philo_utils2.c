/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 09:52:45 by ihamani           #+#    #+#             */
/*   Updated: 2025/07/05 15:17:20 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	time_getter(int flag)
{
	static size_t	start_time;
	struct timeval	tv;
	size_t			now_ms;

	gettimeofday(&tv, NULL);
	now_ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	if (!flag)
	{
		start_time = now_ms;
		return (0);
	}
	else
		return (now_ms - start_time);
}

bool	check_all_finished(t_philo *philo)
{
	int	i;
	int	n;

	pthread_mutex_lock(&philo->sdata->meals);
	if (philo->sdata->number_of_time_eat == 0)
		return (pthread_mutex_unlock(&philo->sdata->meals), false);
	pthread_mutex_unlock(&philo->sdata->meals);
	i = 0;
	n = philo[i].sdata->number_of_philo;
	pthread_mutex_lock(&philo->sdata->meals);
	while (i < n)
	{
		if (philo[i].finshed != 1)
		{
			pthread_mutex_unlock(&philo->sdata->meals);
			return (false);
		}
		i++;
	}
	pthread_mutex_unlock(&philo->sdata->meals);
	return (true);
}

void	*monitoring(void *tmp)
{
	int		i;
	t_main	*m;

	m = tmp;
	while (!check_all_finished(m->philo))
	{
		i = 0;
		usleep(100);
		while (i < m->sdata.number_of_philo)
		{
			pthread_mutex_lock(&m->sdata.meals);
			if (m->philo[i].finshed)
			{
				pthread_mutex_unlock(&m->sdata.meals);
				i++;
				continue ;
			}
			pthread_mutex_unlock(&m->sdata.meals);
			if (check_is_dead(&m->philo[i]))
				return (NULL);
			i++;
		}
	}
	return (NULL);
}

void	*s_case(void *tmp)
{
	t_main	*m;

	m = tmp;
	pthread_mutex_lock(m->philo->r_fork);
	print_eat_fork(m->philo, 1);
	if (check_is_dead(m->philo))
		return (pthread_mutex_unlock(m->philo->r_fork), NULL);
	return (pthread_mutex_unlock(m->philo->r_fork), NULL);
}

void	free_all(t_main *m)
{
	free(m->sdata.forks);
	free(m->philo);
}

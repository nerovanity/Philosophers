/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 09:52:45 by ihamani           #+#    #+#             */
/*   Updated: 2025/06/17 14:10:32 by ihamani          ###   ########.fr       */
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

	i = 0;
	n = philo[i].sdata->number_of_philo;
	while (i < n)
	{
		if (philo[i].finshed != 1)
			return (false);
		i++;
	}
	return (true);
}

void	*monitoring(void *tmp)
{
	int		i;
	t_main	*m;

	m = tmp;
	while (1)
	{
		i = 0;
		while (i < m->sdata.number_of_philo)
		{
			usleep(1000);
			if (check_is_dead(&m->philo[i]))
				return (NULL);
			if (check_all_finished(m->philo))
				return (pthread_mutex_lock(&m->sdata.finished),
					m->sdata.all_finished = 1,
					pthread_mutex_unlock(&m->sdata.finished), NULL);
			pthread_mutex_lock(&m->sdata.meals);
			if (m->sdata.number_of_time_eat > 0
				&& m->philo[i].teat == m->sdata.number_of_time_eat)
				m->philo[i].finshed = 1;
			pthread_mutex_unlock(&m->sdata.meals);
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
	return (NULL);
}

void	free_all(t_main *m)
{
	free(m->sdata.forks);
	free(m->philo);
}

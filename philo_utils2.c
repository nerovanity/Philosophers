/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 09:52:45 by ihamani           #+#    #+#             */
/*   Updated: 2025/06/09 12:58:01 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	time_getter(int flag)
{
	static size_t	time;
	struct timeval	tv;

	if (!flag)
	{
		gettimeofday(&tv, NULL);
		time = tv.tv_usec;
		return (0);
	}
	else
	{
		gettimeofday(&tv, NULL);
		return (tv.tv_usec - time);
	}
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	printf("%ld %d has taken a fork\n", time_getter(1), philo->id + 1);
	pthread_mutex_lock(philo->l_fork);
	printf("%ld %d has taken a fork\n", time_getter(1), philo->id + 1);
	philo->last_eat = time_getter(1);
	printf("%ld %d is eating\n", philo->last_eat, philo->id + 1);
	ft_sleep(philo->sdata->time_to_eat);
	philo->teat++;
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	philo_sleep(t_philo *philo)
{
	printf("%ld %d is sleeping\n", time_getter(1), philo->id + 1);
	ft_sleep(philo->sdata->time_to_sleep);
}

void	*routing(void *tmp)
{
	t_philo	*philo;

	philo = tmp;
	printf("thread Number %d\n", philo->id + 1);
	while (philo->dead == 0 && philo->finshed == 0
		&& !check_is_dead(philo))
	{
		if ((philo->id + 1) % 2 == 0)
		{
			eat(philo);
			philo_sleep(philo);
			printf("%ld %d is thinking\n", time_getter(1), philo->id + 1);
		}
		else
		{
			ft_sleep(philo->sdata->time_to_eat);
			printf("%ld %d is thinking\n", time_getter(1), philo->id + 1);
			eat(philo);
			philo_sleep(philo);
		}
	}
	return (NULL);
}

void	*monitoring(void *tmp)
{
	int		i;
	t_main	*m;

	m = tmp;
	i = 0;
	while (i < m->sdata.number_of_philo)
	{
		sleep(1000);
		if (m->sdata.number_of_time_eat != -1
			&& m->philo[i].teat == m->sdata.number_of_time_eat)
			m->philo[i].finshed = 1;
		if (m->philo[i].dead)
			close_threads(m);
		i++;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 09:52:45 by ihamani           #+#    #+#             */
/*   Updated: 2025/06/11 14:40:06 by ihamani          ###   ########.fr       */
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

void	eat_even(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print_eat_fork(philo, 1);
	pthread_mutex_lock(philo->r_fork);
	print_eat_fork(philo, 1);
	print_eat_fork(philo, 0);
	pthread_mutex_lock(&philo->sdata->meals);
	philo->last_eat = time_getter(1);
	philo->teat++;
	pthread_mutex_unlock(&philo->sdata->meals);
	ft_sleep(philo->sdata->time_to_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->sdata->print);
	printf("%ld %d is sleeping\n", time_getter(1), philo->id + 1);
	pthread_mutex_unlock(&philo->sdata->print);
	ft_sleep(philo->sdata->time_to_sleep);
}

void	*routing(void *tmp)
{
	t_philo	*philo;

	philo = tmp;
	while (!loop_check(philo))
	{
		if ((philo->id + 1) % 2 == 0)
		{
			eat_even(philo);
			philo_sleep(philo);
			print_think(philo);
		}
		else
		{
			print_think(philo);
			ft_sleep(20);
			eat_odd(philo);
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
	while (1)
	{
		i = 0;
		while (i < m->sdata.number_of_philo)
		{
			ft_sleep(10);
			if (check_is_dead(&m->philo[i]))
				return (NULL);
			pthread_mutex_lock(&m->sdata.meals);
			if (m->sdata.number_of_time_eat != -1
				&& m->philo[i].teat == m->sdata.number_of_time_eat)
				m->philo[i].finshed = 1;
			pthread_mutex_unlock(&m->sdata.meals);
			i++;
		}
	}
	return (NULL);
}

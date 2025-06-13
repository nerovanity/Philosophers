/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 09:52:45 by ihamani           #+#    #+#             */
/*   Updated: 2025/06/13 15:18:44 by ihamani          ###   ########.fr       */
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
			ft_sleep(10, &m->philo[i]);
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

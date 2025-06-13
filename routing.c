/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:17:36 by ihamani           #+#    #+#             */
/*   Updated: 2025/06/13 15:23:36 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	eat_even(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	if (check_is_dead(philo))
		return (pthread_mutex_unlock(philo->l_fork), false);
	print_eat_fork(philo, 1);
	pthread_mutex_lock(philo->r_fork);
	if (check_is_dead(philo))
		return (pthread_mutex_unlock(philo->l_fork),
			pthread_mutex_unlock(philo->r_fork), false);
	print_eat_fork(philo, 1);
	pthread_mutex_lock(&philo->sdata->meals);
	philo->last_eat = time_getter(1);
	print_eat_fork(philo, 0);
	philo->teat++;
	pthread_mutex_unlock(&philo->sdata->meals);
	ft_sleep(philo->sdata->time_to_eat, philo);
	if (check_is_dead(philo))
		return (pthread_mutex_unlock(philo->l_fork),
			pthread_mutex_unlock(philo->r_fork), false);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (true);
}

bool	eat_odd(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	if (check_is_dead(philo))
		return (pthread_mutex_unlock(philo->r_fork), false);
	print_eat_fork(philo, 1);
	pthread_mutex_lock(philo->l_fork);
	if (check_is_dead(philo))
		return (pthread_mutex_unlock(philo->l_fork), false);
	print_eat_fork(philo, 1);
	pthread_mutex_lock(&philo->sdata->meals);
	philo->last_eat = time_getter(1);
	print_eat_fork(philo, 0);
	philo->teat++;
	pthread_mutex_unlock(&philo->sdata->meals);
	if (check_is_dead(philo))
		return (pthread_mutex_unlock(philo->r_fork),
			pthread_mutex_unlock(philo->l_fork), false);
	ft_sleep(philo->sdata->time_to_eat, philo);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	return (true);
}

bool	routing_even(t_philo *philo)
{
	if (!eat_even(philo))
		return (false);
	if (!philo_sleep(philo))
		return (false);
	if (check_is_dead(philo))
		return (false);
	print_think(philo);
	usleep(10);
	return (true);
}

bool	routing_odd(t_philo *philo)
{
	print_think(philo);
	usleep(10);
	if (!eat_odd(philo))
		return (false);
	if (check_is_dead(philo))
		return (false);
	philo_sleep(philo);
	return (true);
}

void	*routing(void *tmp)
{
	t_philo	*philo;

	philo = tmp;
	while (!loop_check(philo))
	{
		if ((philo->id + 1) % 2 == 0)
		{
			if (!routing_even(philo))
				break ;
		}
		else
		{
			if (!routing_odd(philo))
				break ;
		}
	}
	return (NULL);
}

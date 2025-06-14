/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:17:36 by ihamani           #+#    #+#             */
/*   Updated: 2025/06/14 13:43:17 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	eat_even(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	if (check_is_dead(philo))
		return (pthread_mutex_unlock(philo->r_fork), false);
	print_eat_fork(philo, 1);
	pthread_mutex_lock(philo->l_fork);
	if (check_is_dead(philo))
		return (pthread_mutex_unlock(philo->r_fork),
			pthread_mutex_unlock(philo->l_fork), false);
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

bool	eat_odd(t_philo *philo)
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
	if (check_is_dead(philo))
		return (pthread_mutex_unlock(philo->l_fork),
			pthread_mutex_unlock(philo->r_fork), false);
	ft_sleep(philo->sdata->time_to_eat, philo);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (true);
}

void	routing_even(t_philo *philo)
{
	if (!eat_even(philo))
		return ;
	if (!philo_sleep(philo))
		return ;
	if (check_is_dead(philo))
		return ;
	print_think(philo);
	usleep(300);
}

void	routing_odd(t_philo *philo)
{
	if (!eat_odd(philo))
		return ;
	if (!philo_sleep(philo))
		return ;
	if (check_is_dead(philo))
		return ;
	print_think(philo);
}

void	*routing(void *tmp)
{
	t_philo	*philo;

	philo = tmp;
	if ((philo->id + 1) % 2 != 0)
	{
		print_think(philo);
		usleep(100);
	}
	print_think(philo);
	while (!philo->sdata->all_finished && !check_is_dead(philo))
	{
		if ((philo->id + 1) % 2 == 0)
			routing_even(philo);
		else
			routing_odd(philo);
	}
	return (NULL);
}

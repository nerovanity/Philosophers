/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:17:36 by ihamani           #+#    #+#             */
/*   Updated: 2025/07/05 15:08:13 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	eat_even(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	if (is_dead(philo))
		return (pthread_mutex_unlock(philo->r_fork), false);
	print_eat_fork(philo, 1);
	pthread_mutex_lock(philo->l_fork);
	if (is_dead(philo))
		return (pthread_mutex_unlock(philo->r_fork),
			pthread_mutex_unlock(philo->l_fork), false);
	print_eat_fork(philo, 1);
	pthread_mutex_lock(&philo->sdata->meals);
	philo->last_eat = time_getter(1);
	print_eat_fork(philo, 0);
	philo->teat++;
	pthread_mutex_unlock(&philo->sdata->meals);
	if (is_dead(philo))
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
	if (is_dead(philo))
		return (pthread_mutex_unlock(philo->l_fork), false);
	print_eat_fork(philo, 1);
	pthread_mutex_lock(philo->r_fork);
	if (is_dead(philo))
		return (pthread_mutex_unlock(philo->l_fork),
			pthread_mutex_unlock(philo->r_fork), false);
	print_eat_fork(philo, 1);
	pthread_mutex_lock(&philo->sdata->meals);
	philo->last_eat = time_getter(1);
	print_eat_fork(philo, 0);
	philo->teat++;
	pthread_mutex_unlock(&philo->sdata->meals);
	if (is_dead(philo))
		return (pthread_mutex_unlock(philo->l_fork),
			pthread_mutex_unlock(philo->r_fork), false);
	ft_sleep(philo->sdata->time_to_eat, philo);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (true);
}

void	routine_even(t_philo *philo)
{
	if (!eat_even(philo))
		return ;
	pthread_mutex_lock(&philo->sdata->meals);
	if (philo->sdata->number_of_time_eat > 0
		&& philo->teat == philo->sdata->number_of_time_eat)
	{
		philo->finshed = 1;
		pthread_mutex_unlock(&philo->sdata->meals);
		return ;
	}
	pthread_mutex_unlock(&philo->sdata->meals);
	if (!philo_sleep(philo))
		return ;
	if (is_dead(philo))
		return ;
	print_think(philo);
}

void	routine_odd(t_philo *philo)
{
	if (!eat_odd(philo))
		return ;
	pthread_mutex_lock(&philo->sdata->meals);
	if (philo->sdata->number_of_time_eat > 0
		&& philo->teat == philo->sdata->number_of_time_eat)
	{
		philo->finshed = 1;
		pthread_mutex_unlock(&philo->sdata->meals);
		return ;
	}
	pthread_mutex_unlock(&philo->sdata->meals);
	if (!philo_sleep(philo))
		return ;
	if (is_dead(philo))
		return ;
	print_think(philo);
}

void	*routine(void *tmp)
{
	t_philo	*philo;
	int		is_finished;

	philo = tmp;
	is_finished = 0;
	if ((philo->id + 1) % 2 != 0)
		usleep(500);
	while (!is_finished && !is_dead(philo))
	{
		if ((philo->id + 1) % 2 == 0)
			routine_even(philo);
		else
			routine_odd(philo);
		pthread_mutex_lock(&philo->sdata->meals);
		is_finished = philo->finshed;
		pthread_mutex_unlock(&philo->sdata->meals);
	}
	return (NULL);
}

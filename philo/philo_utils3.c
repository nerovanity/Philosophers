/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 12:45:23 by ihamani           #+#    #+#             */
/*   Updated: 2025/06/28 16:12:14 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	close_threads(t_main *m)
{
	int	i;

	i = 0;
	while (i < m->sdata.number_of_philo)
	{
		pthread_join(m->philo[i].thread, 0);
		i++;
	}
	pthread_join(m->monitor, 0);
}

void	print_eat_fork(t_philo *philo, int flag)
{
	if (philo->sdata->died)
		return ;
	if (!flag)
	{
		pthread_mutex_lock(&philo->sdata->print);
		printf("%ld %d is eating\n", philo->last_eat, philo->id + 1);
		pthread_mutex_unlock(&philo->sdata->print);
	}
	else
	{
		pthread_mutex_lock(&philo->sdata->print);
		printf("%ld %d has taken a fork\n", time_getter(1), philo->id + 1);
		pthread_mutex_unlock(&philo->sdata->print);
	}
}

bool	philo_sleep(t_philo *philo)
{
	if (is_dead(philo))
		return (false);
	pthread_mutex_lock(&philo->sdata->print);
	printf("%ld %d is sleeping\n", time_getter(1), philo->id + 1);
	pthread_mutex_unlock(&philo->sdata->print);
	ft_sleep(philo->sdata->time_to_sleep, philo);
	return (true);
}

void	print_think(t_philo *philo)
{
	if (is_dead(philo))
		return ;
	pthread_mutex_lock(&philo->sdata->print);
	printf("%ld %d is thinking\n", time_getter(1), philo->id + 1);
	pthread_mutex_unlock(&philo->sdata->print);
}

void	destroting_mutexs(t_main *m)
{
	int	i;

	i = 0;
	while (i < m->sdata.number_of_philo)
		pthread_mutex_destroy(&m->sdata.forks[i++]);
	pthread_mutex_destroy(&m->sdata.is_dead);
	pthread_mutex_destroy(&m->sdata.meals);
	pthread_mutex_destroy(&m->sdata.print);
	pthread_mutex_destroy(&m->sdata.loop_check);
	pthread_mutex_destroy(&m->sdata.finished);
}

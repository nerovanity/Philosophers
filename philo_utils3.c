/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 12:45:23 by ihamani           #+#    #+#             */
/*   Updated: 2025/06/11 15:08:38 by ihamani          ###   ########.fr       */
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

bool	eat_odd(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	if (check_is_dead(philo))
		return (false);
	print_eat_fork(philo, 1);
	pthread_mutex_lock(philo->l_fork);
	if (check_is_dead(philo))
		return (false);
	print_eat_fork(philo, 1);
	pthread_mutex_lock(&philo->sdata->meals);
	philo->last_eat = time_getter(1);
	print_eat_fork(philo, 0);
	philo->teat++;
	pthread_mutex_unlock(&philo->sdata->meals);
	if (check_is_dead(philo))
		return (false);
	ft_sleep(philo->sdata->time_to_eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	return (true);
}

bool	loop_check(t_philo *philo)
{
	bool	flag;

	flag = true;
	if (philo->finshed == 0 && philo->dead == 0 && !check_is_dead(philo))
		flag = false;
	return (flag);
}

void	print_eat_fork(t_philo *philo, int flag)
{
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

void	print_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->sdata->print);
	printf("%ld %d is thinking\n", time_getter(1), philo->id + 1);
	pthread_mutex_unlock(&philo->sdata->print);
}

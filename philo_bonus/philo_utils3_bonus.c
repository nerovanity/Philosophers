/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils3_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 10:34:57 by ihamani           #+#    #+#             */
/*   Updated: 2025/06/30 15:47:44 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_sleep(t_philo *philo, t_main *m)
{
	sem_wait(philo->sems->dying);
	sem_post(philo->sems->dying);
	sem_wait(m->sems.is_dead);
	if (philo->dead)
	{
		sem_post(m->sems.is_dead);
		sem_wait(philo->sems->dying);
		exit(2);
	}
	sem_post(m->sems.is_dead);
	sem_wait(m->sems.print);
	printf("%ld %d is sleeping\n", time_getter(1), philo->id + 1);
	sem_post(m->sems.print);
	ft_sleep(m->sdata.time_to_sleep, philo);
}

void	print_think(t_philo *philo, t_main *m)
{
	sem_wait(philo->sems->dying);
	sem_post(philo->sems->dying);
	sem_wait(m->sems.is_dead);
	if (philo->dead)
	{
		sem_post(m->sems.is_dead);
		sem_wait(philo->sems->dying);
		exit(2);
	}
	sem_post(m->sems.is_dead);
	sem_wait(m->sems.print);
	printf("%ld %d is thinking\n", time_getter(1), philo->id + 1);
	sem_post(m->sems.print);
}

void	*is_finished(void *tmp)
{
	t_main	*m;
	int		i;

	i = 0;
	m = tmp;
	while (i < m->sdata.number_of_philo)
	{
		sem_wait(m->sems.finished);
		i++;
	}
	while (i)
	{
		sem_post(m->sems.finished);
		i--;
	}
	handle_dead(m);
	return (NULL);
}

void	check_if_finshed(t_main *m)
{
	int	i;

	usleep(1000);
	i = m->sdata.number_of_philo;
	if (pthread_create(&m->checker, 0, is_finished, m) != 0)
	{
		while (i)
		{
			sem_post(m->sems.finished);
			i--;
		}
	}
	pthread_detach(m->checker);
}

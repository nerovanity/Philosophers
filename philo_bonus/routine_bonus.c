/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 10:48:37 by ihamani           #+#    #+#             */
/*   Updated: 2025/06/29 14:25:24 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_philo(t_philo *philo, int i, t_main *m)
{
	philo->finished = 0;
	philo->id = i;
	philo->dead = 0;
	philo->leat = time_getter(1);
	philo->sdata = &m->sdata;
	philo->sems = &m->sems;
}

void	a_routine(t_philo *philo, t_main *m)
{
	sem_wait(m->sems.forks);
	print_eat_fork(philo, m, 1);
	sem_wait(m->sems.forks);
	print_eat_fork(philo, m, 1);
	sem_wait(m->sems.eating);
	philo->leat = time_getter(1);
	sem_post(m->sems.eating);
	print_eat_fork(philo, m, 0);
	ft_sleep(m->sdata.time_to_eat, philo);
	sem_post(m->sems.forks);
	sem_post(m->sems.forks);
	philo_sleep(philo, m);
	print_think(philo, m);
}

void	routine(t_philo *philo, t_main *m)
{
	int	is_dead;

	if ((philo->id + 1) % 2 != 0)
	{
		print_think(philo, m);
		usleep(100);
	}
	is_dead = 0;
	while (!is_dead)
	{
		a_routine(philo, m);
		sem_wait(m->sems.is_dead);
		is_dead = philo->dead;
		sem_post(m->sems.is_dead);
	}
}

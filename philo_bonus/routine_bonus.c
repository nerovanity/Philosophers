/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 10:48:37 by ihamani           #+#    #+#             */
/*   Updated: 2025/07/05 11:13:11 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_philo(t_philo *philo, int i, t_main *m)
{
	philo->id = i;
	philo->leat = time_getter(1);
	philo->sdata = &m->sdata;
	philo->sems = &m->sems;
	philo->neat = 0;
	philo->finished = 0;
}

void	close_sems(t_main *m)
{
	sem_close(m->sems.eating);
	sem_close(m->sems.forks);
	sem_close(m->sems.print);
	sem_close(m->sems.finished);
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
	ft_sleep(m->sdata.time_to_eat);
	sem_wait(m->sems.eating);
	philo->neat++;
	sem_post(m->sems.eating);
	sem_post(m->sems.forks);
	sem_post(m->sems.forks);
	philo_sleep(philo, m);
	print_think(philo, m);
}

void	routine(t_philo *philo, t_main *m)
{
	int		tmp;

	tmp = 0;
	if ((philo->id + 1) % 2 != 0)
		usleep(1000);
	while (!tmp)
	{
		a_routine(philo, m);
		sem_wait(philo->sems->finished);
		tmp = philo->finished;
		sem_post(philo->sems->finished);
	}
	exit(0);
}

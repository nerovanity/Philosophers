/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 10:48:37 by ihamani           #+#    #+#             */
/*   Updated: 2025/07/02 20:24:08 by ihamani          ###   ########.fr       */
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
}

void	close_sems(t_main *m)
{
	sem_close(m->sems.eating);
	sem_close(m->sems.forks);
	sem_close(m->sems.print);
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

void	handle_finished(t_main *m)
{
	t_pids	*head;
	int		i;

	i = 0;
	head = m->lst_pid;
	while (head)
	{
		kill(head->id, SIGKILL);
		head = head->next;
	}
}

void	routine(t_philo *philo, t_main *m)
{
	if ((philo->id + 1) % 2 != 0)
	{
		print_think(philo, m);
		usleep(1000);
	}
	while (1)
		a_routine(philo, m);
}

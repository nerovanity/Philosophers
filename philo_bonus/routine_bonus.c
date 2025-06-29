/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 10:48:37 by ihamani           #+#    #+#             */
/*   Updated: 2025/06/29 11:33:08 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_philo(t_philo *philo, int i, t_main *m)
{
	philo->eating = sem_open("eating", O_CREAT, 0, 666);
	if (philo->eating == SEM_FAILED)
	{
		sem_close(m->sems.forks);
		sem_close(m->sems.print);
		ft_putstr_fd("eating sem failed\n", 2);
		exit(3);
	}
	sem_unlink("eating");
	philo->finished = 0;
	philo->id = i;
	philo->leat = time_getter(1);
	philo->sdata = &m->sdata;
}

void	a_routine(t_philo *philo, t_main *m)
{
	sem_wait(m->sems.forks);
	print_eat_fork(philo, m, 1);
	sem_wait(m->sems.forks);
	print_eat_fork(philo, m, 1);
	sem_wait(philo->eating);
	philo->leat = time_getter(1);
	sem_post(philo->eating);
	print_eat_fork(philo, m, 0);
	ft_sleep(m->sdata.time_to_eat);
	philo_sleep(philo, m);
	print_think(philo, m);
}

void	routine(t_philo *philo, t_main *m)
{
	if ((philo->id + 1) % 2 != 0)
	{
		print_think(philo, m);
		usleep(100);
	}
	while (1)
		a_routine(philo, m);
}

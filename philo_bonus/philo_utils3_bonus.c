/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils3_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 10:34:57 by ihamani           #+#    #+#             */
/*   Updated: 2025/06/29 14:06:04 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_sleep(t_philo *philo, t_main *m)
{
	sem_wait(m->sems.is_dead);
	if (philo->dead)
	{
		sem_post(m->sems.is_dead);
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
	sem_wait(m->sems.is_dead);
	if (philo->dead)
	{
		sem_post(m->sems.is_dead);
		exit(2);
	}
	sem_post(m->sems.is_dead);
	sem_wait(m->sems.print);
	printf("%ld %d is thinking\n", time_getter(1), philo->id + 1);
	sem_post(m->sems.print);
}

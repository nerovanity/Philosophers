/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 10:48:37 by ihamani           #+#    #+#             */
/*   Updated: 2025/06/28 16:54:10 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_philo(t_philo *philo, int i)
{
	philo->eating = sem_open("eating", O_CREAT);
	if (philo->eating == SEM_FAILED)
	{
		ft_putstr_fd("child sem_open failed", 2);
		exit(1);
	}
	sem_unlink("eating");
	philo->is_dead = sem_open("dead", O_CREAT);
	if (philo->dead == SEM_FAILED)
	{
		sem_close(philo->eating);
		ft_putstr_fd("child sem_open failed", 2);
		exit(1);
	}
	sem_unlink("dead");
	philo->eating = 0;
	philo->finished = 0;
	philo->id = i;
	philo->leat = time_getter(1);
}

void	routine(t_philo *philo)
{
	t_philo	philo;

	if ((philo->id + 1) % 2 != 0)
	{
		print_thinking(&philo);
		usleep(10);
	}
	while (!philo->dead)
	{
		if ((philo->id + 1) % 2 == 0)
			routine_even(philo);
		else
			routine_odd(philo);
	}
}

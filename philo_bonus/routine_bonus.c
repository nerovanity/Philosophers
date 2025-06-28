/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 10:48:37 by ihamani           #+#    #+#             */
/*   Updated: 2025/06/28 14:04:43 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_philo(t_philo *philo, int i)
{
	philo->eating = sem_open("finished", O_CREAT);
	philo->is_dead = sem_open("dead", O_CREAT);
	if (philo->finished == SEM_FAILED || philo->is_dead == SEM_FAILED)
	{
		ft_putstr_fd("child sem_open failed", 2);
		exit(1);
	}
	philo->eating = 0;
	philo->finished = 0;
	philo->id = i;
}

void	routine(t_main *m, int i)
{
	t_philo	philo;

	init_philo(&philo, i);
	if ((philo.id + 1) % 2 != 0)
	{
		print_thinking(&philo);
		usleep(10);
	}
	while (!philo.dead)
	{
		if ((philo.id + 1) % 2 == 0)
			routine_even(&philo);
		else
			routine_odd(&philo);
	}
}

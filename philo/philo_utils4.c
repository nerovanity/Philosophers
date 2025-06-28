/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 10:08:53 by ihamani           #+#    #+#             */
/*   Updated: 2025/06/28 10:36:19 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	failed_mutex(t_sdata *sdata, int flag)
{
	int	i;

	i = 0;
	while (i < sdata->number_of_philo)
		pthread_mutex_destroy(&sdata->forks[i++]);
	if (flag >= 1)
		pthread_mutex_destroy(&sdata->is_dead);
	else if (flag >= 2)
		pthread_mutex_destroy(&sdata->meals);
	else if (flag >= 3)
		pthread_mutex_destroy(&sdata->print);
	else if (flag == 4)
		pthread_mutex_destroy(&sdata->finished);
}

int	ext_philo_exe(t_main *m)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < m->sdata.number_of_philo)
	{
		if (pthread_create(&m->philo[i].thread, NULL,
				routine, &m->philo[i]) != 0)
		{
			m->failed = 1;
			while (j < i)
				pthread_join(m->philo[j++].thread, 0);
			pthread_join(m->monitor, 0);
			return (1);
		}
		i++;
	}
	return (0);
}

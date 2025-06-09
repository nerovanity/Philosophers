/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 12:45:23 by ihamani           #+#    #+#             */
/*   Updated: 2025/06/09 12:49:01 by ihamani          ###   ########.fr       */
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
}

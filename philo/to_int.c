/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_int.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 23:11:37 by ihamani           #+#    #+#             */
/*   Updated: 2025/06/28 16:10:31 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_arg(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (((str[i] < '0' && str[i] > '9') && str[i] != ' '
				&& str[i] != '+'))
		{
			ft_putstr_fd(" Please provide a valid number\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

int	to_int(char *str)
{
	int	n;

	if (check_arg(str) == 1)
		return (0);
	n = ft_atoi(str);
	return (n);
}

bool	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->sdata->is_dead);
	if (philo->sdata->died || philo->dead == 1)
	{
		pthread_mutex_unlock(&philo->sdata->is_dead);
		return (true);
	}
	pthread_mutex_unlock(&philo->sdata->is_dead);
	return (false);
}

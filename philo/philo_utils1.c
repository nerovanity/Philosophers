/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 23:06:23 by ihamani           #+#    #+#             */
/*   Updated: 2025/06/28 14:10:59 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
		write(fd, &str[i++], 1);
}

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
			while (j < i)
				pthread_join(m->philo[j++].thread, 0);
			pthread_join(m->monitor, 0);
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_sleep(size_t micro, t_philo *philo)
{
	size_t	start;

	start = time_getter(1) * 1000;
	while ((time_getter(1) * 1000) - start < micro * 1000)
	{
		if (check_is_dead(philo))
			break ;
		usleep(100);
	}
}

int	ext_mutex(t_sdata *sdata)
{
	if (pthread_mutex_init(&sdata->is_dead, NULL) != 0)
		return (failed_mutex(sdata, 0), 1);
	if (pthread_mutex_init(&sdata->meals, NULL) != 0)
		return (failed_mutex(sdata, 1), 1);
	if (pthread_mutex_init(&sdata->print, NULL) != 0)
		return (failed_mutex(sdata, 2), 1);
	if (pthread_mutex_init(&sdata->loop_check, NULL) != 0)
		return (failed_mutex(sdata, 3), 1);
	if (pthread_mutex_init(&sdata->finished, NULL) != 0)
		return (failed_mutex(sdata, 4), 1);
	return (0);
}

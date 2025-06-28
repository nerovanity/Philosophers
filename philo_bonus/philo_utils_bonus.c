/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:57:41 by ihamani           #+#    #+#             */
/*   Updated: 2025/06/28 16:54:32 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
		write(fd, &str[i++], 1);
}

void	*monitoring(void *tmp)
{
	t_philo	*philo;

	philo = tmp;
	while (1)
	{
		
	}
}

void	child(t_main *m, int i)
{
	t_philo	philo;

	time_getter(0);
	init_philo(&philo, i);
	routine(&philo);
	if (pthread_create(philo.monitor, NULL, monitoring, &philo) != 0)
		exit(1);
}

size_t	time_getter(int flag)
{
	static size_t	start_time;
	struct timeval	tv;
	size_t			now_ms;

	gettimeofday(&tv, NULL);
	now_ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	if (!flag)
	{
		start_time = now_ms;
		return (0);
	}
	else
		return (now_ms - start_time);
}

void	ft_sleep(size_t micro)
{
	size_t	start;

	start = time_getter(1) * 1000;
	while ((time_getter(1) * 1000) - start < micro * 1000)
		usleep(100);
}

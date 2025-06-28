/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:57:41 by ihamani           #+#    #+#             */
/*   Updated: 2025/06/28 09:53:56 by ihamani          ###   ########.fr       */
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

static int	skip_ws(const char *str)
{
	int	i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int			i;
	long long	r;
	long long	max;

	i = 0;
	r = 0;
	max = 2147483647;
	i = skip_ws(str);
	if (str[i] == '+')
		i++;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		if (r > (max - (str[i] - '0')) / 10)
			return (-1);
		r = (r * 10) + (str[i++] - '0');
	}
	i += skip_ws(&str[i]);
	if (str[i])
		return (0);
	return (r);
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

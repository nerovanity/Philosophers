/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 23:06:23 by ihamani           #+#    #+#             */
/*   Updated: 2025/06/13 15:11:10 by ihamani          ###   ########.fr       */
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

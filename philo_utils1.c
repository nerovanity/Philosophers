/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 23:06:23 by ihamani           #+#    #+#             */
/*   Updated: 2025/03/05 01:47:45 by ihamani          ###   ########.fr       */
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

void	throw_err(char *str)
{
	ft_putstr_fd(str, 2);
	exit(1);
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

	i = 0;
	r = 0;
	i = skip_ws(str);
	if (str[i] == '+')
		i++;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
		r = (r * 10) + (str[i++] - '0');
	i += skip_ws(&str[i]);
	if (str[i])
		throw_err("Please provide a valid number\n");
	return (r);
}

void	ft_sleep(int micro)
{
	usleep(micro * 1000);
}


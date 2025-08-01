/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 22:42:53 by ihamani           #+#    #+#             */
/*   Updated: 2025/07/05 10:35:32 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	args_err(void)
{
	ft_putstr_fd("./philo ", 2);
	ft_putstr_fd("number_of_philosophers ", 2);
	ft_putstr_fd("time_to_die time_to_eat time_to_sleep optional", 2);
	ft_putstr_fd("[number_of_times_each_philosopher_must_eat]\n", 2);
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

int	parsing(int ac, char **av, t_sdata *sdata)
{
	if (ac < 5 || ac > 6)
		return (args_err(), 1);
	sdata->number_of_philo = to_int(av[1]);
	if (sdata->number_of_philo <= 0)
		return (ft_putstr_fd("not a valid number of philos\n", 2), 1);
	if (sdata->number_of_philo >= 250)
		return (ft_putstr_fd("please provide ", 2),
			ft_putstr_fd("number of philos less than 250\n", 2), 1);
	sdata->time_to_die = to_int(av[2]);
	sdata->time_to_eat = to_int(av[3]);
	sdata->time_to_sleep = to_int(av[4]);
	sdata->died = false;
	if (sdata->time_to_die <= 59 || sdata->time_to_eat <= 59
		|| sdata->time_to_sleep <= 59)
		return (ft_putstr_fd("not a valid arguments\n", 2), 1);
	if (ac == 6)
	{
		sdata->number_of_time_eat = to_int(av[5]);
		if (sdata->number_of_time_eat <= 0)
			return (ft_putstr_fd("not a valid arguments\n", 2), 1);
	}
	else
		sdata->number_of_time_eat = 0;
	return (0);
}

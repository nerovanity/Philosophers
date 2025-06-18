/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 22:42:53 by ihamani           #+#    #+#             */
/*   Updated: 2025/06/14 09:54:10 by ihamani          ###   ########.fr       */
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

int	parsing(int ac, char **av, t_sdata *sdata)
{
	if (ac < 5 || ac > 6)
		return (args_err(), 1);
	sdata->number_of_philo = to_int(av[1]);
	if (sdata->number_of_philo == 0)
		return (ft_putstr_fd("not a valid number of philos\n", 2), 1);
	sdata->time_to_die = to_int(av[2]);
	sdata->time_to_eat = to_int(av[3]);
	sdata->time_to_sleep = to_int(av[4]);
	sdata->died = false;
	sdata->all_finished = 0;
	if (!sdata->time_to_die || !sdata->time_to_die
		|| !sdata->time_to_sleep)
		return (ft_putstr_fd("not a valid arguments\n", 2), 1);
	if (ac == 6)
	{
		sdata->number_of_time_eat = to_int(av[5]);
		if (!sdata->number_of_time_eat)
			return (ft_putstr_fd("not a valid arguments\n", 2), 1);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 22:42:53 by ihamani           #+#    #+#             */
/*   Updated: 2025/06/09 12:52:01 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	args_err(void)
{
	ft_putstr_fd("./philo ", 2);
	ft_putstr_fd("number_of_philosophers ", 2);
	ft_putstr_fd("time_to_die time_to_eat time_to_sleep optional", 2);
	ft_putstr_fd("[number_of_times_each_philosopher_must_eat]\n", 2);
	exit(1);
}

void	parsing(int ac, char **av, t_sdata *sdata)
{
	if (ac < 5 || ac > 6)
		args_err();
	sdata->number_of_philo = to_int(av[1]);
	if (!sdata->number_of_philo)
		throw_err("Philosophers number is ranging from 1 to N\n");
	printf("%d\n", sdata->number_of_philo);
	sdata->time_to_die = to_int(av[2]);
	printf("%zu\n", sdata->time_to_die);
	sdata->time_to_eat = to_int(av[3]);
	printf("%d\n", sdata->time_to_eat);
	sdata->time_to_sleep = to_int(av[4]);
	printf("%d\n", sdata->time_to_sleep);
	if (ac == 6)
	{
		sdata->number_of_time_eat = to_int(av[5]);
		printf("%d\n", sdata->number_of_time_eat);
	}
}

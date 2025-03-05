/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 22:42:53 by ihamani           #+#    #+#             */
/*   Updated: 2025/03/05 00:22:14 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	args_err()
{
	ft_putstr_fd("./philo ", 2);
	ft_putstr_fd("number_of_philosophers ", 2);
	ft_putstr_fd("time_to_die time_to_eat time_to_sleep optional", 2);
	ft_putstr_fd("[number_of_times_each_philosopher_must_eat]\n", 2);
	exit(1);
}

void	parsing(int ac, char **av, t_rules *rules)
{
	if (ac < 5 || ac > 6)
		args_err();
	rules->number_of_philo = to_int(av[1]);
	if (!rules->number_of_philo)
		throw_err("Philosophers number is ranging from 1 to n\n");
	printf("%d\n", rules->number_of_philo);
	rules->time_to_die = to_int(av[2]);
	printf("%d\n", rules->time_to_die);
	rules->time_to_eat = to_int(av[3]);
	printf("%d\n", rules->time_to_eat);
	rules->time_to_sleep = to_int(av[4]);
	printf("%d\n", rules->time_to_sleep);
	if (ac == 6)
	{
		rules->number_of_time_eat = to_int(av[5]);
		printf("%d\n", rules->number_of_time_eat);
	}
}

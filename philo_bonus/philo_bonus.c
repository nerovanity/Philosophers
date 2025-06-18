/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:30:32 by ihamani           #+#    #+#             */
/*   Updated: 2025/06/18 15:01:18 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char **av)
{
	t_sdata	sdata;

	if (parsing(ac, av, &sdata) == 1)
		exit(1);
	printf("number_of_philo: %d| ", sdata.number_of_philo);
	printf("time_to_die: %zu | ", sdata.time_to_die);
	printf("time_to_eat: %d | ", sdata.time_to_eat);
	printf("time_to_sleep: %d | ", sdata.time_to_sleep);
	printf("number_of_time_eat: %d\n", sdata.number_of_time_eat);
}

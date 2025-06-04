/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 01:07:18 by ihamani           #+#    #+#             */
/*   Updated: 2025/06/02 16:57:01 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*philo_init(t_philo *philo, t_rules rules)
{
	int		i;
	char	*forks;

	i = 0;
	forks = malloc(sizeof(char) * (rules.number_of_philo + 1));
	if (!forks)
	{
		perror("malloc");
		exit(1);
	}
	forks[rules.number_of_philo] = '\0';
	while (i < rules.number_of_philo)
	{
		philo[i].time_eat = rules.time_to_eat;
		philo[i].time_die = rules.time_to_die;
		philo[i].id = i;
		philo[i].finshed = 0;
		philo[i].dead = 0;
		philo[i].r_fork = &forks[(i + 1) % rules.number_of_philo];
		philo[i].l_fork = &forks[i];
		philo[i].neat = 0;
		i++;
	}
	return (forks);
}

int	main(int ac, char **av)
{
	t_rules		rules;
	t_philo		*philo;
	int			i = 0;

	parsing(ac, av, &rules);
	philo = malloc(sizeof(t_philo) * rules.number_of_philo);
	philo_init(philo, rules);
	while (i < rules.number_of_philo)
	{
		printf("Philo %d: time_eat=%d, time_die=%d, finshed=%d, dead=%d, r_fork=%p, l_fork=%p\n",
			philo[i].id,
			philo[i].time_eat,
			philo[i].time_die,
			philo[i].finshed,
			philo[i].dead,
			(void *)philo[i].r_fork,
			(void *)philo[i].l_fork);
		i++;
	}
}

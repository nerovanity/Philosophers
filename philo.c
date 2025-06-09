/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 01:07:18 by ihamani           #+#    #+#             */
/*   Updated: 2025/06/09 11:58:10 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	void	init_mutex(t_sdata *sdata)
{
	int	i;

	i = 0;
	while (i < sdata->number_of_philo)
		pthread_mutex_init(&sdata->forks[i++], NULL);
}

static int	philo_init(t_philo *philo, t_sdata *sdata)
{
	int		i;

	i = 0;
	sdata->forks = malloc(sizeof(pthread_mutex_t) * sdata->number_of_philo);
	if (!sdata->forks)
		return (write(2, "Malloc\n", 7), free(philo), 1);
	memset(sdata->forks, 0, sizeof(pthread_mutex_t) * sdata->number_of_philo);
	init_mutex(sdata);
	while (i < sdata->number_of_philo)
	{
		philo[i].id = i;
		philo[i].finshed = 0;
		philo[i].dead = 0;
		philo[i].r_fork = &sdata->forks[(i + 1) % sdata->number_of_philo];
		philo[i].l_fork = &sdata->forks[i];
		philo[i].teat = 0;
		philo[i].sdata = sdata;
		i++;
	}
	return (0);
}

static int	philo_exe(t_main *m)
{
	int	i;

	i = 0;
	time_getter(0);
	while (i < m->sdata.number_of_philo)
	{
		if (pthread_create(&m->philo[i].thread, NULL,
				routing, &m->philo[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_main	m;

	parsing(ac, av, &m.sdata);
	m.philo = malloc(sizeof(t_philo) * m.sdata.number_of_philo);
	if (!m.philo)
		return (write(2, "Malloc\n", 7), 1);
	memset(m.philo, 0, sizeof(t_philo) * m.sdata.number_of_philo);
	if (philo_init(m.philo, &m.sdata) == 1)
		return (1);
	if (philo_exe(&m) != 0)
		return (1);
}

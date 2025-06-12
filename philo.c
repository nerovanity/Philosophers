/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 01:07:18 by ihamani           #+#    #+#             */
/*   Updated: 2025/06/12 16:58:41 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	void	init_mutex(t_sdata *sdata)
{
	int	i;

	i = 0;
	while (i < sdata->number_of_philo)
		pthread_mutex_init(&sdata->forks[i++], NULL);
	pthread_mutex_init(&sdata->is_dead, NULL);
	pthread_mutex_init(&sdata->meals, NULL);
	pthread_mutex_init(&sdata->print, NULL);
	pthread_mutex_init(&sdata->loop_check, NULL);
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
		philo[i].last_eat = time_getter(1);
		philo[i].teat = 0;
		philo[i].sdata = sdata;
		i++;
	}
	return (0);
}

bool	check_is_dead(t_philo *philo)
{
	size_t			n;

	pthread_mutex_lock(&philo->sdata->meals);
	n = time_getter(1) - philo->last_eat;
	pthread_mutex_unlock(&philo->sdata->meals);
	pthread_mutex_lock(&philo->sdata->is_dead);
	if (philo->sdata->died || philo->dead == 1)
	{
		pthread_mutex_unlock(&philo->sdata->is_dead);
		return (true);
	}
	if (n > philo->sdata->time_to_die)
	{
		pthread_mutex_lock(&philo->sdata->print);
		printf("%ld %d died\n", time_getter(1), philo->id + 1);
		pthread_mutex_unlock(&philo->sdata->print);
		philo->dead = 1;
		philo->sdata->died = true;
		pthread_mutex_unlock(&philo->sdata->is_dead);
		return (true);
	}
	pthread_mutex_unlock(&philo->sdata->is_dead);
	return (false);
}

static int	philo_exe(t_main *m)
{
	int	i;

	i = 0;
	if (pthread_create(&m->monitor, NULL,
			monitoring, m) != 0)
		return (1);
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

	if (parsing(ac, av, &m.sdata) == 1)
		return (1);
	m.philo = malloc(sizeof(t_philo) * m.sdata.number_of_philo);
	if (!m.philo)
		return (write(2, "Malloc\n", 7), 1);
	memset(m.philo, 0, sizeof(t_philo) * m.sdata.number_of_philo);
	time_getter(0);
	if (philo_init(m.philo, &m.sdata) == 1)
		return (1);
	if (philo_exe(&m) != 0)
		return (1);
	close_threads(&m);
}

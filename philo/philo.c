/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 01:07:18 by ihamani           #+#    #+#             */
/*   Updated: 2025/07/06 09:52:10 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	int	init_mutex(t_sdata *sdata)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < sdata->number_of_philo)
	{
		if (pthread_mutex_init(&sdata->forks[i++], NULL) != 0)
		{
			while (j < i)
				pthread_mutex_destroy(&sdata->forks[j++]);
			ft_putstr_fd("mutex_init failed\n", 2);
			return (1);
		}
	}
	if (ext_mutex(sdata) == 1)
		return (ft_putstr_fd("mutex_init failed\n", 2), 1);
	return (0);
}

static int	philo_init(t_philo *philo, t_sdata *sdata)
{
	int		i;

	i = 0;
	sdata->forks = malloc(sizeof(pthread_mutex_t) * sdata->number_of_philo);
	if (!sdata->forks)
		return (write(2, "Malloc failed\n", 7), 1);
	memset(sdata->forks, 0, sizeof(pthread_mutex_t) * sdata->number_of_philo);
	if (init_mutex(sdata) == 1)
		return (1);
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
	if (n > (size_t)philo->sdata->time_to_die)
	{
		usleep(1000);
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
	if (m->sdata.number_of_philo == 1)
	{
		if (pthread_create(&m->philo->thread, NULL, s_case, m) != 0)
			return (1);
	}
	else
	{
		if (ext_philo_exe(m) == 1)
			return (1);
	}
	if (pthread_create(&m->monitor, NULL,
			monitoring, m) != 0)
	{
		i = 0;
		while (i < m->sdata.number_of_philo)
			pthread_join(m->philo[i++].thread, 0);
		return (1);
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
		return (write(2, "Malloc failed\n", 7), 1);
	memset(m.philo, 0, sizeof(t_philo) * m.sdata.number_of_philo);
	time_getter(0);
	if (philo_init(m.philo, &m.sdata) == 1)
		return (free(m.philo), 1);
	if (philo_exe(&m) != 0)
		return (free_all(&m), destroting_mutexs(&m), 1);
	close_threads(&m);
	destroting_mutexs(&m);
	free_all(&m);
}

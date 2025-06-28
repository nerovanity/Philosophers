/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:30:32 by ihamani           #+#    #+#             */
/*   Updated: 2025/06/28 10:47:55 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static	void	run_philo(t_main *m, int i)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == -1)
		fork_err();
	else if (!pid)
		routine(m, i);
	else
	{
		lst_pid_add(m->lst_pid, new_node(pid));
		waitpid(pid, &status, 0);
		if (WEXITSTATUS(status) == 1)
			m->sdata.died = 1;
	}
}

static int	exe_philos(t_main *m)
{
	int	i;

	i = 0;
	while (i < m->sdata.number_of_philo)
	{
		run_philo(m, i);
		i++;
	}
}

static	int	init_sem(t_main *m)
{
	m->sems.forks = sem_open("sem_forks", O_CREAT, 0,
			0644, m->sdata.number_of_philo);
	m->sems.print = sem_open("sem_print", O_CREAT);
	m->sems.is_dead = sem_open("sem_is_dead", O_CREAT, 0,
			0644, m->sdata.number_of_philo);
	sem_unlink("sem_forks");
	sem_unlink("sem_print");
}

int	main(int ac, char **av)
{
	t_main	m;

	if (parsing(ac, av, &m.sdata) == 1)
		exit(1);
	m.lst_pid = NULL;
	if (init_sem(&m) == 1)
		exit(1);
	if (exe_philos(&m) == 1)
		exit(1);
}

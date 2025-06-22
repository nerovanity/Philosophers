/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:30:32 by ihamani           #+#    #+#             */
/*   Updated: 2025/06/22 10:15:24 by ihamani          ###   ########.fr       */
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
	m->sems.forks = sem_open("forks", O_CREAT, 0, m->sdata.number_of_philo);
	m->sems.print = sem_open("print", O_CREAT);
}

int	main(int ac, char **av)
{
	t_main	m;

	if (parsing(ac, av, &m.sdata) == 1)
		exit(1);
	m.lst_pid = NULL;
	// printf("number_of_philo: %d| ", m.sdata.number_of_philo);
	// printf("time_to_die: %zu | ", m.sdata.time_to_die);
	// printf("time_to_eat: %d | ", m.sdata.time_to_eat);
	// printf("time_to_sleep: %d | ", m.sdata.time_to_sleep);
	// printf("number_of_time_eat: %d\n", m.sdata.number_of_time_eat);
	if (init_sem(&m) == 1)
		exit(1);
	if (exe_philos(&m) == 1)
		exit(1);
}

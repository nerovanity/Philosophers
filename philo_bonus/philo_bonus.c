/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:30:32 by ihamani           #+#    #+#             */
/*   Updated: 2025/07/01 15:48:17 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static	void	run_philo(t_main *m, int i)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		fork_err();
	else if (!pid)
		child(m, i);
	else
		lst_pid_add(&m->lst_pid, new_node(pid));
}

static void	exe_philos(t_main *m)
{
	int		i;
	int		status;

	i = 0;
	status = 0;
	time_getter(0);
	while (i < m->sdata.number_of_philo)
		run_philo(m, i++);
	check_if_finshed(m);
	wait(&status);
	if (WEXITSTATUS(status) == 2)
		handle_dead(m);
}

static void	ext_init_sem(t_main *m)
{
	m->sems.eating = sem_open("/eating", O_CREAT, 0666, 1);
	if (m->sems.eating == SEM_FAILED)
	{
		sem_close(m->sems.forks);
		sem_close(m->sems.print);
		ft_putstr_fd("eating sem failed\n", 2);
		exit(3);
	}
	sem_unlink("/eating");
	m->sems.is_dead = sem_open("/dead", O_CREAT, 0666, 1);
	if (m->sems.is_dead == SEM_FAILED)
	{
		sem_close(m->sems.forks);
		sem_close(m->sems.print);
		sem_close(m->sems.eating);
		ft_putstr_fd("dead sem failed\n", 2);
		exit(3);
	}
	sem_unlink("/dead");
	m->sems.dying = sem_open("/dying", O_CREAT,
			0666, 1);
	sem_unlink("/dying");
	m->sems.finished = sem_open("/finished", O_CREAT,
			0666, m->sdata.number_of_philo);
	sem_unlink("/finished");
}

static	void	init_sem(t_main *m)
{
	m->sems.forks = sem_open("/sem_forks", O_CREAT,
			0666, m->sdata.number_of_philo);
	if (m->sems.forks == SEM_FAILED)
	{
		ft_putstr_fd("forks sem failed", 2);
		exit(1);
	}
	sem_unlink("/sem_forks");
	m->sems.print = sem_open("/sem_print", O_CREAT, 0666, 1);
	if (m->sems.print == SEM_FAILED)
	{
		perror("print");
		ft_putstr_fd("print sem failed", 2);
		sem_close(m->sems.forks);
		exit(1);
	}
	sem_unlink("/sem_print");
	ext_init_sem(m);
}

int	main(int ac, char **av)
{
	t_main	m;

	if (parsing(ac, av, &m.sdata) == 1)
		exit(1);
	m.lst_pid = NULL;
	init_sem(&m);
	exe_philos(&m);
	free_lst(&m.lst_pid);
}

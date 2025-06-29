/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 10:02:57 by ihamani           #+#    #+#             */
/*   Updated: 2025/06/29 14:25:59 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	fork_err(void)
{
	while (wait(NULL) != -1)
		continue ;
	ft_putstr_fd("Fork failed", 2);
	exit(1);
}

t_pids	*new_node(pid_t pid)
{
	t_pids	*new;

	new = malloc(sizeof(t_pids));
	new->id = pid;
	return (new);
}

void	lst_pid_add(t_pids **lst, t_pids *new)
{
	t_pids	*head;

	if (new == NULL || lst == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	head = *lst;
	while (head->next)
		head = head->next;
	head->next = new;
}

void	handle_dead(t_main *m)
{
	t_pids	*head;

	head = m->lst_pid;
	while (head)
	{
		kill(head->id, SIGKILL);
		head = head->next;
	}
}

void	print_eat_fork(t_philo *philo, t_main *m, int flag)
{
	sem_wait(m->sems.is_dead);
	if (philo->dead)
	{
		sem_post(m->sems.is_dead);
		exit(2);
	}
	sem_post(m->sems.is_dead);
	if (!flag)
	{
		sem_wait(m->sems.print);
		printf("%ld %d is eating\n", philo->leat, philo->id + 1);
		sem_post(m->sems.print);
	}
	else
	{
		sem_wait(m->sems.print);
		printf("%ld %d has taken a fork\n", time_getter(1), philo->id + 1);
		sem_post(m->sems.print);
	}
}

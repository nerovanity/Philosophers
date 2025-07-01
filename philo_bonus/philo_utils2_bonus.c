/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 10:02:57 by ihamani           #+#    #+#             */
/*   Updated: 2025/07/01 17:57:13 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	fork_err(void)
{
	ft_putstr_fd("Fork failed", 2);
	while (wait(NULL) != -1)
		continue ;
	exit(1);
}

t_pids	*new_node(pid_t pid)
{
	t_pids	*new;

	new = malloc(sizeof(t_pids));
	new->id = pid;
	new->next = NULL;
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
	int		i;

	i = 0;
	head = m->lst_pid;
	while (head)
	{
		kill(head->id, SIGKILL);
		head = head->next;
	}
	while (sem_post(m->sems.finished) != 0)
		continue ;
	sem_post(m->sems.print);
}

void	print_eat_fork(t_philo *philo, t_main *m, int flag)
{
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils3_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 10:34:57 by ihamani           #+#    #+#             */
/*   Updated: 2025/07/03 17:32:40 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_sleep(t_philo *philo, t_main *m)
{
	sem_wait(m->sems.print);
	printf("%ld %d is sleeping\n", time_getter(1), philo->id + 1);
	sem_post(m->sems.print);
	ft_sleep(m->sdata.time_to_sleep);
}

void	print_think(t_philo *philo, t_main *m)
{
	if (m->sdata.number_of_philo > 1)
	{
		sem_wait(m->sems.print);
		printf("%ld %d is thinking\n", time_getter(1), philo->id + 1);
		sem_post(m->sems.print);
	}
}

void	free_lst(t_pids **lst)
{
	t_pids	*head;
	t_pids	*prv;

	if (lst == NULL || *lst == NULL)
		return ;
	head = *lst;
	while (head)
	{
		prv = head;
		head = head->next;
		free(prv);
	}
	*lst = NULL;
}

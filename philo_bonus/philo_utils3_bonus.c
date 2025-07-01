/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils3_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 10:34:57 by ihamani           #+#    #+#             */
/*   Updated: 2025/07/01 18:07:38 by ihamani          ###   ########.fr       */
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
	sem_wait(m->sems.print);
	printf("%ld %d is thinking\n", time_getter(1), philo->id + 1);
	sem_post(m->sems.print);
}

void	*is_finished(void *tmp)
{
	t_main	*m;
	int		i;

	i = 0;
	m = tmp;
	while (i < m->sdata.number_of_philo)
	{
		sem_wait(m->sems.finished);
		i++;
	}
	sem_wait(m->sems.print);
	handle_finished(m);
	while (sem_post(m->sems.finished) != 0)
		continue ;
	sem_close(m->sems.finished);
	return (NULL);
}

void	check_if_finshed(t_main *m)
{
	int	i;

	usleep(1000);
	i = m->sdata.number_of_philo;
	if (pthread_create(&m->checker, 0, is_finished, m) != 0)
	{
		while (i)
		{
			sem_post(m->sems.finished);
			i--;
		}
	}
	pthread_detach(m->checker);
}

void	free_lst(t_pids **lst)
{
	t_pids	*head;
	t_pids	*prv;

	head = *lst;
	while (head)
	{
		prv = head;
		head = head->next;
		free(prv);
	}
	*lst = NULL;
}

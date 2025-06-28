/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:36:26 by ihamani           #+#    #+#             */
/*   Updated: 2025/06/28 14:01:51 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>
# include <semaphore.h>
# include <fcntl.h>

typedef struct s_sdata
{
	int					number_of_philo;
	size_t				time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_time_eat;
	int					died;
	int					fork_fail;
}	t_sdata;

typedef struct s_philo
{
	sem_t	*eating;
	sem_t	*is_dead;
	int		finished;
	int		dead;
	int		id;
}	t_philo;

typedef struct s_sems
{
	sem_t	*forks;
	sem_t	*print;
	sem_t	*is_dead;
}	t_sems;

typedef struct s_main
{
	t_sdata	sdata;
	t_sems	sems;
	t_pids	**lst_pid;
}	t_main;

typedef struct s_pids
{
	pid_t	id;
	void	*next;
}	t_pids;

int		parsing(int ac, char **av, t_sdata *rules);
void	ft_putstr_fd(char *str, int fd);
int		to_int(char *str);
int		ft_atoi(const char *str);
void	ft_sleep(size_t micro);
size_t	time_getter(int flag);
void	fork_err(void);
t_pids	*new_node(pid_t pid);
void	lst_pid_add(t_pids **lst, t_pids *new);

#endif
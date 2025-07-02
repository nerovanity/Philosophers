/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:36:26 by ihamani           #+#    #+#             */
/*   Updated: 2025/07/02 19:46:45 by ihamani          ###   ########.fr       */
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
# include <signal.h>
# include <sys/wait.h>

typedef struct s_sdata
{
	int					number_of_philo;
	size_t				time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_time_eat;
}	t_sdata;

typedef struct s_sems
{
	sem_t	*forks;
	sem_t	*print;
	sem_t	*eating;
	sem_t	*finished;
}	t_sems;

typedef struct s_philo
{
	pthread_t	monitor;
	size_t		leat;
	int			neat;
	int			id;
	t_sdata		*sdata;
	t_sems		*sems;
}	t_philo;

typedef struct s_pids
{
	pid_t	id;
	void	*next;
}	t_pids;

typedef struct s_main
{
	t_sdata		sdata;
	t_sems		sems;
	pthread_t	checker;
	t_pids		*lst_pid;
}	t_main;

int		parsing(int ac, char **av, t_sdata *rules);
void	ft_putstr_fd(char *str, int fd);
int		to_int(char *str);
int		ft_atoi(const char *str);
void	ft_sleep(size_t micro);
size_t	time_getter(int flag);
void	fork_err(void);
t_pids	*new_node(pid_t pid);
void	lst_pid_add(t_pids **lst, t_pids *new);
void	child(t_main *m, int i);
void	routine(t_philo *philo, t_main *m);
void	init_philo(t_philo *philo, int i, t_main *m);
void	handle_dead(t_main *m);
void	print_think(t_philo *philo, t_main *m);
void	philo_sleep(t_philo *philo, t_main *m);
void	print_eat_fork(t_philo *philo, t_main *m, int flag);
void	check_if_finshed(t_main *m);
void	free_lst(t_pids **lst);
void	close_sems(t_main *m);
void	handle_finished(t_main *m);

#endif
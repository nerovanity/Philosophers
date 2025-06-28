/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 01:07:24 by ihamani           #+#    #+#             */
/*   Updated: 2025/06/28 16:08:14 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_sdata
{
	int					number_of_philo;
	size_t				time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_time_eat;
	int					all_finished;
	pthread_mutex_t		*forks;
	pthread_mutex_t		is_dead;
	pthread_mutex_t		meals;
	pthread_mutex_t		print;
	pthread_mutex_t		finished;
	pthread_mutex_t		loop_check;
	bool				died;
}	t_sdata;

typedef struct s_philo
{
	pthread_t			thread;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		*l_fork;
	int					finshed;
	int					dead;
	size_t				last_eat;
	int					id;
	t_sdata				*sdata;
	int					teat;
}					t_philo;

typedef struct s_main
{
	pthread_t			monitor;
	t_sdata				sdata;
	t_philo				*philo;
}				t_main;

int		parsing(int ac, char **av, t_sdata *rules);
void	ft_putstr_fd(char *str, int fd);
int		to_int(char *str);
int		ft_atoi(const char *str);
void	ft_sleep(size_t micro, t_philo *philo);
size_t	time_getter(int flag);
void	*routine(void *tmp);
void	*monitoring(void *m);
bool	check_is_dead(t_philo *philo);
void	close_threads(t_main *m);
bool	eat_odd(t_philo *philo);
void	print_think(t_philo *philo);
void	print_eat_fork(t_philo *philo, int flag);
bool	philo_sleep(t_philo *philo);
bool	check_all_finished(t_philo *philo);
void	*s_case(void *m);
void	free_all(t_main *m);
void	destroting_mutexs(t_main *m);
void	failed_mutex(t_sdata *sdata, int i);
int		ext_mutex(t_sdata *sdata);
int		ext_philo_exe(t_main *m);
bool	is_dead(t_philo *philo);

#endif
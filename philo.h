/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 01:07:24 by ihamani           #+#    #+#             */
/*   Updated: 2025/06/09 11:58:38 by ihamani          ###   ########.fr       */
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

typedef struct s_sdata
{
	int					number_of_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_time_eat;
	pthread_mutex_t		*forks;
	pthread_t			*tmonitor;
}	t_sdata;

typedef struct s_philo
{
	pthread_t			thread;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		*l_fork;
	int					finshed;
	int					dead;
	int					id;
	t_sdata				*sdata;
	int					teat;
}					t_philo;

typedef struct s_main
{
	t_sdata				sdata;
	t_philo				*philo;
}				t_main;

void	parsing(int ac, char **av, t_sdata *rules);
void	ft_putstr_fd(char *str, int fd);
void	throw_err(char *str);
int		to_int(char *str);
int		ft_atoi(const char *str);
void	ft_sleep(int micro);
size_t	time_getter(int flag);
void	*routing(void *tmp);

#endif
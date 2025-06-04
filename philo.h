/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 01:07:24 by ihamani           #+#    #+#             */
/*   Updated: 2025/06/02 16:56:39 by ihamani          ###   ########.fr       */
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

typedef struct s_rules
{
	int	number_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_time_eat;
}	t_rules;

typedef struct s_philo
{
	pthread_t	*thread;
	void		*r_fork;
	void		*l_fork;
	int			time_eat;
	int			time_die;
	int			finshed;
	int			dead;
	int			id;
	int			neat;
}					t_philo;


void	parsing(int ac, char **av, t_rules *rules);
void	ft_putstr_fd(char *str, int fd);
void	throw_err(char *str);
int		to_int(char *str);
int		ft_atoi(const char *str);
void	ft_sleep(int micro);

#endif
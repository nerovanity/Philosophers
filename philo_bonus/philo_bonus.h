/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:36:26 by ihamani           #+#    #+#             */
/*   Updated: 2025/06/18 15:00:03 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

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
}	t_sdata;

int		parsing(int ac, char **av, t_sdata *rules);
void	ft_putstr_fd(char *str, int fd);
int		to_int(char *str);
int		ft_atoi(const char *str);
void	ft_sleep(size_t micro);
size_t	time_getter(int flag);

#endif
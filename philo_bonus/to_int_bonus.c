/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_int_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 23:11:37 by ihamani           #+#    #+#             */
/*   Updated: 2025/06/18 14:40:57 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	check_arg(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (((str[i] < '0' && str[i] > '9') && str[i] != ' '
				&& str[i] != '+'))
		{
			ft_putstr_fd(" Please provide a valid number\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

int	to_int(char *str)
{
	int	n;

	if (check_arg(str) == 1)
		return (0);
	n = ft_atoi(str);
	return (n);
}

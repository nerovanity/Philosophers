/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_int.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 23:11:37 by ihamani           #+#    #+#             */
/*   Updated: 2025/03/05 00:18:56 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	check_arg(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (((str[i] < '0' && str[i] > '9') && str[i] != ' '
				&& str[i] != '+'))
			throw_err(" Please provide a valid number");
		i++;
	}
}

int	to_int(char *str)
{
	check_arg(str);
	return (ft_atoi(str));
}

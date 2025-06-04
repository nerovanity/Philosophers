/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_int.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 23:11:37 by ihamani           #+#    #+#             */
/*   Updated: 2025/05/25 16:59:55 by ihamani          ###   ########.fr       */
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
			throw_err(" Please provide a valid number\n");
		i++;
	}
}

int	to_int(char *str)
{
	int	n;

	check_arg(str);
	n = ft_atoi(str);
	if (n == -1)
		throw_err("Please provide a valid number\n");
	return (n);
}

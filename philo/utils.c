/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acinca-f <acinca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 10:27:28 by acinca-f          #+#    #+#             */
/*   Updated: 2023/05/01 11:30:12 by acinca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int		sign;
	long	r;

	r = 0;
	sign = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n'
		|| *str == '\v' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= 48 && *str <= 57)
	{
		r = r * 10 + *str - '0';
		str++;
	}
	return (sign * (int)r);
}

t_time	real_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

t_time	app_time(t_table *table)
{
	return (real_time() - table->initial_time);
}

void	smart_sleep(t_time ms, t_table *table)
{
	t_time	start;

	start = app_time(table);
	while (app_time(table) < start + ms)
		continue ;
}

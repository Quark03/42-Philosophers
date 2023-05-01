/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acinca-f <acinca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 10:38:22 by acinca-f          #+#    #+#             */
/*   Updated: 2023/05/01 11:42:13 by acinca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (ac < 4)
		return (1);
	while (i < ac && av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if ((av[i][j] < '0' || av[i][j] > '9') && j != 0)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	load_table(t_table *table, int ac, char **av)
{
	if (check_args(ac, av))
		return (1);
	table->initial_time = real_time();
	table->total_ate = 0;
	table->stop = 0;
	table->num_philo = ft_atoi(av[1]);
	table->time_die = ft_atoi(av[2]);
	table->time_eat = ft_atoi(av[3]);
	table->time_sleep = ft_atoi(av[4]);
	table->must_eat = -1;
	if (table->num_philo <= 0 || table->time_die <= 0
		|| table->time_eat <= 0 || table->time_sleep <= 0)
		return (1);
	if (av[5])
	{
		table->must_eat = ft_atoi(av[5]);
		if (table->must_eat <= 0)
			return (1);
	}
	return (0);
}

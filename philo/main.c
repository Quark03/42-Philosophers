/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acinca-f <acinca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 10:26:16 by acinca-f          #+#    #+#             */
/*   Updated: 2023/05/01 11:48:07 by acinca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	load_philos(t_philo *philos, t_table *table,
	pthread_mutex_t *forks, pthread_mutex_t *print)
{
	int	i;

	i = 0;
	while (i < table->num_philo)
	{
		philos[i].ate = 0;
		philos[i].id = i + 1;
		philos[i].table = table;
		philos[i].forks = forks;
		philos[i].print = print;
		i++;
	}
}

int	init_table(t_table **table, int ac, char **av)
{
	*table = (t_table *)malloc(sizeof(t_table));
	if (!*table)
		return (1);
	if (load_table(*table, ac, av))
		return (1);
	return (0);
}

int	init_philos(t_philo **philos, t_table *table,
		pthread_mutex_t *forks, pthread_mutex_t *print)
{
	*philos = (t_philo *)malloc(sizeof(t_philo) * table->num_philo);
	if (!*philos)
		return (1);
	load_philos(*philos, table, forks, print);
	return (0);
}

int	init_mutexes(pthread_mutex_t *forks, pthread_mutex_t *print,
	t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philo)
	{
		if (pthread_mutex_init(&forks[i], NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(print, NULL))
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_table			*table;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print;
	t_philo			*philos;
	pthread_t		*th;

	if (init_table(&table, ac, av))
		return (free_err(table, NULL, NULL, NULL));
	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* table->num_philo);
	if (!forks)
		return (free_err(table, forks, NULL, NULL));
	print = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!print)
		return (free_err(table, forks, print, NULL));
	if (init_philos(&philos, table, forks, print))
		return (free_err(philos, table, forks, print));
	if (init_mutexes(forks, print, table))
		return (free_err(philos, table, forks, print));
	th = malloc(sizeof(pthread_t) * table->num_philo);
	if (!th)
		return (free_err(table, philos, forks, print)
			+ free_err(th, NULL, NULL, NULL));
	return (free_ok(table, forks, print, philos)
		+ free_ok(th, NULL, NULL, NULL));
}

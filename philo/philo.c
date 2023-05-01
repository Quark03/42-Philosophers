/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acinca-f <acinca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:25:05 by acinca-f          #+#    #+#             */
/*   Updated: 2023/05/01 11:46:14 by acinca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_philo *philo, t_time time, char *text)
{
	pthread_mutex_lock(philo->print);
	printf("%lu\t%d %s\n", (unsigned long)time, philo->id, text);
	pthread_mutex_unlock(philo->print);
}

void	*philo_routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	while (p->table->stop == 0)
	{
		if (p->id % 2 == 0)
			smart_sleep(10, p->table);
		pthread_mutex_lock(&p->forks[p->id - 1]);
		print_action(p, app_time(p->table), "has taken a fork");
		pthread_mutex_lock(&p->forks[p->id % p->table->num_philo]);
		print_action(p, app_time(p->table), "has taken a fork");
		print_action(p, app_time(p->table), "is eating");
		p->ate++;
		if (p->ate == p->table->must_eat)
			p->table->total_ate++;
		p->last_meal = app_time(p->table);
		smart_sleep(p->table->time_eat, p->table);
		pthread_mutex_unlock(&p->forks[p->id - 1]);
		pthread_mutex_unlock(&p->forks[p->id % p->table->num_philo]);
		print_action(p, app_time(p->table), "is sleeping");
		smart_sleep(p->table->time_sleep, p->table);
		print_action(p, app_time(p->table), "is thinking");
		smart_sleep(10, p->table);
	}
	return (NULL);
}

int	start_threads(t_table *table, t_philo *philo, pthread_t *th)
{
	int	i;

	i = 0;
	while (i < table->num_philo)
	{
		philo->last_meal = app_time(table);
		if (pthread_create(&th[i], NULL, philo_routine, (void *)&philo[i]))
			return (1);
		if (pthread_detach(th[i]))
			return (1);
		i++;
	}
	return (0);
}

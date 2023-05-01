/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acinca-f <acinca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:25:05 by acinca-f          #+#    #+#             */
/*   Updated: 2023/05/01 14:53:56 by acinca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_philo *philo, t_time time, char *text)
{
	if (philo->table->stop != 0)
		return ;
	pthread_mutex_lock(philo->print);
	if (philo->table->stop != 0)
	{
		pthread_mutex_unlock(philo->print);
		return ;
	}
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
		pthread_mutex_lock(&p->forks[p->id]);
		print_action(p, app_time(p->table), "has taken a fork");
		if (p->table->num_philo == 1)
			return (NULL);
		pthread_mutex_lock(&p->forks[(p->id + 1) % p->table->num_philo]);
		print_action(p, app_time(p->table), "has taken a fork");
		print_action(p, app_time(p->table), "is eating");
		p->ate++;
		p->last_meal = app_time(p->table);
		if (p->ate == p->table->must_eat)
			p->table->total_ate++;
		smart_sleep(p->table->time_eat, p->table);
		pthread_mutex_unlock(&p->forks[p->id]);
		pthread_mutex_unlock(&p->forks[(p->id + 1) % p->table->num_philo]);
		print_action(p, app_time(p->table), "is sleeping");
		smart_sleep(p->table->time_sleep, p->table);
		print_action(p, app_time(p->table), "is thinking");
	}
	return (NULL);
}

void	check_finish(t_table *table, t_philo *philo)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < table->num_philo)
		{
			if (table->total_ate == table->num_philo)
			{
				pthread_mutex_lock(philo[i].print);
				printf("Simulation Finished - All philosophers ate %d times\n",
					table->must_eat);
				table->stop = 1;
				pthread_mutex_unlock(philo[i].print);
				return ;
			} else if (app_time(table) - philo[i].last_meal > table->time_die)
			{
				pthread_mutex_lock(philo[i].print);
				printf("%lu\t%d died\n", app_time(table), philo[i].id);
				table->stop = 1;
				pthread_mutex_unlock(philo[i].print);
				return ;
			}
			i++;
		}
		smart_sleep(5, table);
	}
}

int	start_threads(t_table *table, t_philo *philo, pthread_t *th)
{
	int	i;

	i = 0;
	while (i < table->num_philo)
	{
		philo->last_meal = app_time(table);
		if (pthread_create(&th[i], NULL, philo_routine, (void *)&philo[i]))
		{
			printf("Error creating thread %d\n", i);
			return (1);
		}
		i++;
	}
	check_finish(table, philo);
	i = 0;
	while (i < table->num_philo)
	{
		if (pthread_join(th[i], NULL))
		{
			printf("Error joining thread %d\n", i);
			return (1);
		}
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acinca-f <acinca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 10:26:25 by acinca-f          #+#    #+#             */
/*   Updated: 2023/05/01 11:01:29 by acinca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef unsigned long	t_time;

// Table
typedef struct s_table
{
	t_time	initial_time;
	int		total_ate;
	int		num_philo;
	int		time_die;
	int		time_eat;
	int		time_sleep;
	int		must_eat;
	int		kill;
}	t_table;

// Philo
typedef struct s_philo
{
	int				ate;
	int				id;
	t_table			*table;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print;
	t_time			last_meal;
}	t_philo;

// Init
int		check_args(int ac, char **av);
int		load_table(t_table *table, int ac, char **av);
// Utils
int		ft_atoi(const char *str);
t_time	real_time(void);
t_time	app_time(t_table *table);
void	smart_sleep(t_time ms, t_table *table);
int		free_util(void *p1, void *p2, void *p3, void *p4);

#endif

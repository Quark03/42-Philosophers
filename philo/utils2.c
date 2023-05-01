/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acinca-f <acinca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:28:29 by acinca-f          #+#    #+#             */
/*   Updated: 2023/05/01 11:28:39 by acinca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	free_err(void *p1, void *p2, void *p3, void *p4)
{
	if (p1)
		free(p1);
	if (p2)
		free(p2);
	if (p3)
		free(p3);
	if (p4)
		free(p4);
	return (1);
}

int	free_ok(void *p1, void *p2, void *p3, void *p4)
{
	if (p1)
		free(p1);
	if (p2)
		free(p2);
	if (p3)
		free(p3);
	if (p4)
		free(p4);
	return (0);
}

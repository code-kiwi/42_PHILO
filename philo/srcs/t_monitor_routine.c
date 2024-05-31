/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_monitor_routine.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:55:00 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/31 14:19:21 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

#include "philo.h"

static bool	t_monitor_routine_start(t_monitor *monitor)
{
	bool	error;

	error = false;
	if (monitor == NULL || pthread_mutex_lock(monitor->mutex_start) != 0)
		return (false);
	if (*(monitor->nb_philos_launched) != monitor->nb_philos)
		error = true;
	if (pthread_mutex_unlock(monitor->mutex_start) != 0)
		return (false);
	if (error)
		return (false);
	if (pthread_mutex_lock(&monitor->mutex_monitor_start) != 0)
		return (false);
	monitor->started = true;
	if (pthread_mutex_unlock(&monitor->mutex_monitor_start) != 0)
		return (false);
	return (true);
}

void	*t_monitor_routine(void *monitor_ptr)
{
	t_monitor	*monitor;

	if (monitor_ptr == NULL)
		return (NULL);
	monitor = (t_monitor *) monitor_ptr;
	if (!t_monitor_routine_start(monitor))
		return (t_monitoring_set_error(monitor), NULL);
	return (NULL);
}

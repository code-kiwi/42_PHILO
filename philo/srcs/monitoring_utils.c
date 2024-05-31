/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:55:00 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/31 09:41:34 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

#include "philo.h"

bool	t_monitor_init(t_monitor *monitor)
{
	if (monitor == NULL)
		return (false);
	monitor->thread_created = false;
	monitor->started = false;
	if (pthread_mutex_init(&monitor->mutex, NULL) != 0)
		return (false);
	return (true);
}

bool	is_monitoring_on(t_monitor *monitor)
{
	bool	ret;

	if (monitor == NULL)
		return (false);
	if (pthread_mutex_lock(&monitor->mutex) != 0)
		return (false);
	ret = monitor->started;
	if (pthread_mutex_unlock(&monitor->mutex) != 0)
		return (false);
	return (ret);
}

static bool	t_monitor_start(t_monitor *monitor)
{
	if (monitor == NULL)
		return (false);
	if (pthread_mutex_lock(&monitor->mutex) != 0)
		return (false);
	monitor->started = true;
	if (pthread_mutex_unlock(&monitor->mutex) != 0)
		return (false);
	return (true);
}

void	*monitor_routine(void *monitor_ptr)
{
	t_monitor	*monitor;

	if (monitor_ptr == NULL)
		return (NULL);
	monitor = (t_monitor *) monitor_ptr;
	if (!t_monitor_start(monitor))
		return (NULL);
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_monitor_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:55:00 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/31 14:09:55 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <string.h>

#include "philo.h"

bool	t_monitor_init(t_monitor *monitor, t_philo_data *data)
{
	if (monitor == NULL || data == NULL)
		return (false);
	memset(monitor, 0, sizeof(t_monitor));
	monitor->thread_created = false;
	monitor->started = false;
	monitor->error = false;
	monitor->nb_philos = data->nb_philos;
	monitor->nb_philos_launched = &data->nb_philos_launched;
	monitor->mutex_start = &data->mutex_start;
	monitor->mutex_print = &data->mutex_print;
	if (pthread_mutex_init(&monitor->mutex_monitor_start, NULL) != 0)
		return (false);
	if (pthread_mutex_init(&monitor->mutex_error, NULL) != 0)
	{
		pthread_mutex_destroy(&monitor->mutex_monitor_start);
		return (false);
	}
	return (true);
}

bool	t_monitoring_is_on(t_monitor *monitor)
{
	if (monitor == NULL)
		return (false);
	return (get_mutex_protected_bool(&monitor->mutex_monitor_start, \
		&monitor->started));
}

bool	t_monitoring_set_error(t_monitor *monitor)
{
	if (monitor == NULL)
		return (false);
	if (pthread_mutex_lock(&monitor->mutex_error) != 0)
		return (false);
	monitor->error = true;
	if (pthread_mutex_unlock(&monitor->mutex_error) != 0)
		return (false);
	return (true);
}

bool	t_monitoring_is_on_error(t_monitor *monitor)
{
	if (monitor == NULL)
		return (false);
	return (get_mutex_protected_bool(&monitor->mutex_error, &monitor->error));
}

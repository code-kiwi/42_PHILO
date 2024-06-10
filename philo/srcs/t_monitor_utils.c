/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_monitor_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:55:00 by mhotting          #+#    #+#             */
/*   Updated: 2024/06/10 16:03:27 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <string.h>

#include "philo.h"

/**
 * @brief Initializes the given monitor
 * 
 * Sets all the members of a given monitor according to the given data
 * Instanciates the mutex members
 * @param monitor The monitor to init
 * @param data The project's data from which fields will be taken
 * @return true on SUCCESS, false on ERROR
*/
bool	t_monitor_init(t_monitor *monitor, t_philo_data *data)
{
	if (monitor == NULL || data == NULL)
		return (false);
	memset(monitor, 0, sizeof(t_monitor));
	monitor->thread_created = false;
	monitor->started = false;
	monitor->error = false;
	monitor->nb_meals_limited = data->nb_meals_limited;
	monitor->time_to_die = data->time_to_die;
	monitor->nb_philos = data->nb_philos;
	monitor->nb_philos_launched = &data->nb_philos_launched;
	monitor->philos = data->philos;
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

/**
 * @brief Indicates if the given monitor has been started
 * @param monitor The monitor whose status is checked
 * @return true if the monitor has been started, else false
*/
bool	t_monitoring_is_on(t_monitor *monitor)
{
	if (monitor == NULL)
		return (false);
	return (get_mutex_bool(&monitor->mutex_monitor_start, \
		&monitor->started));
}

/**
 * @brief Sets the given monitor's error flag to true
 * @param monitor The monitor to set on error
 * @return true on SUCCESS, else FALSE
*/
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

/**
 * @brief Indicates if the given monitor is on error
 * @param monitor The monitor whose error status is checked
 * @return true if the monitor is on error, else false
*/
bool	t_monitoring_is_on_error(t_monitor *monitor)
{
	if (monitor == NULL)
		return (false);
	return (get_mutex_bool(&monitor->mutex_error, &monitor->error));
}

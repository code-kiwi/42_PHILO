/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_monitor_routine.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:55:00 by mhotting          #+#    #+#             */
/*   Updated: 2024/06/10 11:50:03 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <errno.h>

#include "philo.h"

static bool	t_monitor_all_finished(t_monitor *monitor)
{
	size_t	i;
	t_philo	*philo;

	if (monitor == NULL || !monitor->nb_meals_limited)
		return (false);
	i = 0;
	while (i < monitor->nb_philos)
	{
		philo = &monitor->philos[i];
		if (get_mutex_bool(philo->mutex_stop, &philo->finished))
			return (false);
		i++;
	}
	return (true);
}

static bool	t_monitor_routine_start(t_monitor *monitor)
{
	bool	error;

	error = false;
	if (monitor == NULL || pthread_mutex_lock(monitor->mutex_start) != 0)
		return (false);
	if (*(monitor->nb_philos_launched) != monitor->nb_philos)
		error = true;
	if (pthread_mutex_unlock(monitor->mutex_start) != 0 || error)
		return (false);
	if (!set_mutex_bool(&monitor->mutex_monitor_start, &monitor->started, true))
		return (false);
	return (true);
}

static bool	t_monitor_routine_loop_death(t_philo *philo)
{
	if (!set_mutex_bool(philo->mutex_stop, philo->stopped, true))
		return (false);
	if (!pprint_death(philo->mutex_print, philo))
		return (false);
	return (true);
}

static bool	t_monitor_routine_loop(t_monitor *monitor)
{
	size_t	i;
	t_philo	*philo;
	long	ts_meal;
	long	ts_curr;

	while (true)
	{
		i = 0;
		if (t_monitor_all_finished(monitor))
			return (true);
		while (i < monitor->nb_philos)
		{
			philo = &monitor->philos[i];
			if (get_mutex_bool(philo->mutex_stop, philo->stopped))
				return (true);
			ts_meal = philo_get_last_meal_start(philo);
			ts_curr = get_ts();
			if (errno != 0 || ts_meal == -1 || ts_curr == -1)
				return (false);
			if (ts_meal != 0 && ts_curr - ts_meal >= monitor->time_to_die)
				return (t_monitor_routine_loop_death(philo));
			i++;
		}
	}
}

void	*t_monitor_routine(void *monitor_ptr)
{
	t_monitor	*monitor;

	if (monitor_ptr == NULL)
		return (NULL);
	monitor = (t_monitor *) monitor_ptr;
	if (!t_monitor_routine_start(monitor))
		return (t_monitoring_set_error(monitor), NULL);
	t_monitor_routine_loop(monitor);
	return (NULL);
}

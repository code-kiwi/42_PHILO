/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 09:41:22 by mhotting          #+#    #+#             */
/*   Updated: 2024/06/19 17:53:44 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <pthread.h>

#include "philo.h"

/**
 * @brief Launches the monitoring thread
 * @param data The project's data
 * @return true in case of SUCCESS, false on ERROR
 */
static bool	launch_monitoring(t_philo_data *data)
{
	t_monitor	*monitor;

	if (data == NULL)
		return (false);
	monitor = &data->monitor;
	if (pthread_create(&monitor->thread, NULL, t_monitor_routine, monitor) != 0)
		return (false);
	monitor->thread_created = true;
	return (true);
}

/**
 * @brief Launches all the threads for the project: for philos and monitoring
 * @param data The project's data
 * @return true in case of SUCCESS, false on ERROR
 */
bool	launch_threads(t_philo_data *data)
{
	size_t	i;
	bool	returned;

	if (data == NULL)
		return (false);
	if (pthread_mutex_lock(&data->mutex_start) != 0)
		return (false);
	i = 0;
	while (i < data->nb_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL, philo_routine, \
			(void *)&data->philos[i]) != 0)
			break ;
		data->nb_philos_launched += 1;
		i++;
	}
	returned = launch_monitoring(data);
	if (pthread_mutex_unlock(&data->mutex_start) != 0 || !returned
		|| data->nb_philos_launched != data->nb_philos)
		return (false);
	return (true);
}

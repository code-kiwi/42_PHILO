/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:38:24 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/30 12:53:50 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <pthread.h>

#include "philo.h"

static bool	launch_monitoring(t_philo_data *data)
{
	t_monitor	*monitor;
	int			returned;

	if (data == NULL)
		return (false);
	monitor = &data->monitor;
	if (pthread_mutex_lock(&monitor->mutex) != 0)
		return (false);
	returned = pthread_create(&monitor->thread, NULL, monitor_routine, monitor);
	if (pthread_mutex_unlock(&monitor->mutex) != 0 || returned != 0)
		return (false);
	return (true);
}

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

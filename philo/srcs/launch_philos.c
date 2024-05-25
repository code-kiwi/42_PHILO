/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:38:24 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/25 14:44:11 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <pthread.h>

#include "philo.h"

bool	launch_philos(t_philo_data *data)
{
	size_t	i;

	if (data == NULL)
		return (false);
	i = 0;
	if (pthread_mutex_lock(&data->mutex_start) != 0)
		return (false);
	while (i < data->nb_philos - 1)
	{
		pthread_create(&data->philos[i].thread, NULL, philo_routine, (void *)&data->philos[i]);
		i += 2;
	}
	i = 1;
	while (i < data->nb_philos - 1)
	{
		pthread_create(&data->philos[i].thread, NULL, philo_routine, (void *)&data->philos[i]);
		i += 2;
	}
	pthread_create(&data->philos[data->nb_philos - 1].thread, NULL, philo_routine, (void *)&data->philos[data->nb_philos - 1]);
	if (pthread_mutex_unlock(&data->mutex_start) != 0)
		return (false);
	return (true);
}
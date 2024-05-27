/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:38:24 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/27 13:57:46 by mhotting         ###   ########.fr       */
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
	while (i < data->nb_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL, philo_routine, (void *)&data->philos[i]) != 0)
			return (false); // destroy all created threads
		i++;
	}
	if (pthread_mutex_unlock(&data->mutex_start) != 0)
		return (false); // destroy all created threads
	return (true);
}
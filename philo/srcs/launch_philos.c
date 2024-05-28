/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:38:24 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/28 22:52:27 by mhotting         ###   ########.fr       */
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
	if (data->nb_philos_launched != data->nb_philos
		|| pthread_mutex_unlock(&data->mutex_start) != 0)
		return (false);
	return (true);
}

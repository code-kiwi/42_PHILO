/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:38:24 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/24 13:23:20 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <pthread.h>

#include "philo.h"

void	launch_philos(t_philo_data *data)
{
	size_t	i;

	if (data == NULL)
		return ;
	i = 0;
	while (i < data->nb_philos - 1)
	{
		pthread_create(&data->philos[0].thread, NULL, philo_routine, (void *)&data->philos[0]);
		i += 2;
	}
	i = 1;
	while (i < data->nb_philos - 1)
	{
		pthread_create(&data->philos[i].thread, NULL, philo_routine, (void *)&data->philos[i]);
		i += 2;
	}
	pthread_create(&data->philos[data->nb_philos - 1].thread, NULL, philo_routine, (void *)&data->philos[data->nb_philos - 1]);
	i = 0;
	while (i < data->nb_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}
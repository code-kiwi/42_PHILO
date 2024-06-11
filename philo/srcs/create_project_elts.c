/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_project_elts.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:00:22 by mhotting          #+#    #+#             */
/*   Updated: 2024/06/10 13:43:46 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <string.h>

#include "philo.h"

/**
 * @brief Create forks for the project's data
 * @param data The project's data
 * @return true in case of SUCCESS, false on ERROR
 */
static bool	create_forks(t_philo_data *data)
{
	size_t	i;

	data->forks = (t_fork *) malloc(data->nb_philos * sizeof(t_fork));
	if (data->forks == NULL)
		return (false);
	i = 0;
	while (i < data->nb_philos)
	{
		if (!t_fork_init(&data->forks[i]))
			break ;
		i++;
	}
	if (i == data->nb_philos)
		return (true);
	while (i > 0)
	{
		t_fork_destroy(&data->forks[i - 1]);
		i--;
	}
	free(data->forks);
	data->forks = NULL;
	return (false);
}

/**
 * @brief Create philos for the project's data
 * @param data The project's data
 * @return true in case of SUCCESS, false on ERROR
 */
static bool	create_philos(t_philo_data *data)
{
	size_t	i;

	if (data == NULL || data->forks == NULL)
		return (false);
	data->philos = (t_philo *) malloc(data->nb_philos * sizeof(t_philo));
	if (data->philos == NULL)
		return (false);
	i = 0;
	while (i < data->nb_philos)
	{
		if (!t_philo_init(&data->philos[i], data, i))
			break ;
		i++;
	}
	if (i == data->nb_philos)
		return (true);
	free(data->philos);
	data->philos = NULL;
	return (false);
}

/**
 * @brief Creates forks, philos and monitor for the project's data
 * @param data The project's data
 * @return true in case of SUCCESS, false on ERROR
 */
bool	create_project_elts(t_philo_data *data)
{
	if (data == NULL)
		return (false);
	if (
		!create_forks(data)
		|| !create_philos(data)
		|| !t_monitor_init(&data->monitor, data)
	)
		return (data_destroy(data), false);
	return (true);
}

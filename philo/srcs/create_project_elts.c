/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_project_elts.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:00:22 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/24 12:50:40 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <string.h>

#include "philo.h"

static bool	create_forks(t_philo_data *data)
{
	size_t	i;

	data->forks = (pthread_mutex_t *) \
		malloc(data->nb_philos * sizeof(pthread_mutex_t));
	if (data->forks == NULL)
		return (false);
	i = 0;
	while (i < data->nb_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			break ;
		i++;
	}
	if (i == data->nb_philos)
		return (true);
	while (i > 0)
	{
		pthread_mutex_destroy(&data->forks[i - 1]);
		i--;
	}
	free(data->forks);
	data->forks = NULL;
	return (false);
}

/**
 * @todo check if timestamp init is not leading to troubles
*/
static void	init_philo(t_philo *philo, t_philo_data *data, size_t index)
{
	if (philo == NULL || data == NULL)
		return ;
	memset(philo, 0, sizeof(t_philo));
	philo->idx = index + 1;
	philo->last_meal_start = get_ts();
	philo->is_dead = false;
	philo->has_dead_friend = false;
	philo->time_to_eat = data->time_to_eat;
	philo->time_to_sleep = data->time_to_sleep;
	philo->mutex_print = &data->mutex_print;
	philo->left_fork = &data->forks[index];
	if (data->nb_philos == 1)
		philo->right_fork = NULL;
	else if (index == data->nb_philos - 1)
		philo->right_fork = &data->forks[0];
	else
		philo->right_fork = &data->forks[index + 1];
	philo->ts_initial = data->ts_initial;
}

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
		init_philo(&data->philos[i], data, i);
		i++;
	}
	return (true);
}

bool	create_project_elts(t_philo_data *data)
{
	if (data == NULL)
		return (false);
	if (!create_forks(data))
		return (data_destroy(data), false);
	if (!create_philos(data))
		return (data_destroy(data), false);
	return (true);
}

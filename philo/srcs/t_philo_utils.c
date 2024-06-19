/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_philo_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:19:40 by mhotting          #+#    #+#             */
/*   Updated: 2024/06/19 17:58:19 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "philo.h"

/**
 * @brief Initializes the given philo
 * 
 * Sets all the members of a given philo according to the given data
 * @param monitor The philo to init
 * @param data The project's data from which fields will be taken
 * @return true on SUCCESS, false on ERROR
*/
bool	t_philo_init(t_philo *philo, t_philo_data *data, size_t index)
{
	if (philo == NULL || data == NULL)
		return (false);
	memset(philo, 0, sizeof(t_philo));
	philo->idx = index + 1;
	philo->time_to_eat = data->time_to_eat;
	philo->time_to_sleep = data->time_to_sleep;
	philo->mutex_print = &data->mutex_print;
	philo->mutex_start = &data->mutex_start;
	philo->mutex_stop = &data->mutex_stop;
	philo->mutex_meal_start = &data->mutex_meal_time;
	philo->left_fork = &data->forks[index];
	if (data->nb_philos != 1)
		philo->right_fork = &data->forks[(index + 1) % data->nb_philos];
	philo->ts_initial = &data->ts_initial;
	philo->nb_philos = data->nb_philos;
	philo->nb_philos_launched = &data->nb_philos_launched;
	philo->nb_meals_req = data->nb_meals_req;
	philo->nb_meals_limited = data->nb_meals_limited;
	philo->monitor = &data->monitor;
	philo->stopped = &data->stopped;
	return (true);
}

/**
 * @brief Sets the philo last meal time
 * 
 * The meal time start is protected by a mutex
 * @param philo The philo whose meal time start needs to be set
 * @return true on SUCCESS, false on ERROR
 */
bool	philo_set_last_meal_start(t_philo *philo)
{
	bool	ret;

	if (philo == NULL)
		return (false);
	ret = true;
	if (pthread_mutex_lock(philo->mutex_meal_start) != 0)
		return (false);
	philo->last_meal_start = get_ts();
	if (philo->last_meal_start == -1)
		ret = false;
	if (*philo->ts_initial == 0)
		*philo->ts_initial = philo->last_meal_start;
	if (pthread_mutex_unlock(philo->mutex_meal_start) != 0)
		return (false);
	return (ret);
}

/**
 * @brief Returns the philo last meal time
 * 
 * The meal time start is protected by a mutex
 * @param philo The philo whose meal time start needs is requested
 * @return The last meal time start
 */
long	philo_get_last_meal_start(t_philo *philo)
{
	long	ts;

	if (philo == NULL)
		return (false);
	if (pthread_mutex_lock(philo->mutex_meal_start) != 0)
		return (-1);
	ts = philo->last_meal_start;
	if (pthread_mutex_unlock(philo->mutex_meal_start) != 0)
		return (-1);
	return (ts);
}

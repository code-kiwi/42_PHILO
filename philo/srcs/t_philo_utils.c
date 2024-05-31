/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_philo_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:19:40 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/31 14:03:40 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "philo.h"

void	t_philo_destroy(t_philo *philo)
{
	if (philo == NULL)
		return ;
	pthread_mutex_destroy(&philo->mutex_meal_start);
	pthread_mutex_destroy(&philo->mutex_stop);
}

static bool	t_philo_init_mutex(t_philo *philo)
{
	if (philo == NULL)
		return (false);
	if (pthread_mutex_init(&philo->mutex_meal_start, NULL) != 0)
		return (false);
	if (pthread_mutex_init(&philo->mutex_stop, NULL) != 0)
	{
		pthread_mutex_destroy(&philo->mutex_meal_start);
		return (false);
	}
	return (true);
}

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
	philo->left_fork = &data->forks[index];
	if (data->nb_philos != 1)
		philo->right_fork = &data->forks[(index + 1) % data->nb_philos];
	philo->ts_initial = data->ts_initial;
	philo->nb_philos = data->nb_philos;
	philo->nb_philos_launched = &data->nb_philos_launched;
	philo->nb_meals_req = data->nb_meals_req;
	philo->nb_meals_limited = data->nb_meals_limited;
	philo->monitor = &data->monitor;
	return (t_philo_init_mutex(philo));
}

bool	philo_set_last_meal_start(t_philo *philo)
{
	bool	ret;

	if (philo == NULL)
		return (false);
	ret = true;
	if (pthread_mutex_lock(&philo->mutex_meal_start) != 0)
		return (false);
	philo->last_meal_start = get_ts();
	if (philo->last_meal_start == -1)
		ret = false;
	if (pthread_mutex_unlock(&philo->mutex_meal_start) != 0)
		return (false);
	return (ret);
}

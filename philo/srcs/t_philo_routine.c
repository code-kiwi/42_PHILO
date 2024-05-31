/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_philo_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:50:32 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/31 15:55:40 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <errno.h>

#include "philo.h"

static bool	philo_routine_wait_monitor(t_philo *philo)
{
	if (philo == NULL || philo->monitor == NULL)
		return (false);
	while (!t_monitoring_is_on(philo->monitor))
	{
		if (errno != 0 || !ft_usleep(500))
		{
			philo->stopped = true;
			return (false);
		}
	}
	return (true);
}

static bool	philo_routine_init(t_philo *philo)
{
	if (philo == NULL || pthread_mutex_lock(philo->mutex_start) != 0)
		return (false);
	if (*(philo->nb_philos_launched) != philo->nb_philos)
		philo->stopped = true;
	if (pthread_mutex_unlock(philo->mutex_start) != 0)
		return (false);
	if (
		philo->stopped || !philo_set_last_meal_start(philo)
		|| (philo->idx % 2 == 0 && !ft_msleep(philo->time_to_eat / 2))
	)
	{
		philo->stopped = true;
		return (false);
	}
	return (true);
}

void	*philo_routine(void *philo_ptr)
{
	t_philo	*philo;

	if (philo_ptr == NULL)
		return (NULL);
	philo = (t_philo *) philo_ptr;
	if (!philo_routine_wait_monitor(philo) || !philo_routine_init(philo))
		return (NULL);
	while (true)
	{
		if (!philo_routine_forks(philo))
			break ;
		if (!philo_routine_eat(philo))
			break ;
		if (philo->nb_meals_limited
			&& philo->nb_meals_had == philo->nb_meals_req)
			return (NULL);
		if (!philo_routine_sleep(philo))
			break ;
		if (!philo_routine_think(philo))
			break ;
	}
	philo->stopped = true;
	return (NULL);
}

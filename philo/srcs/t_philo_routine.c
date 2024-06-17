/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_philo_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codekiwi <codekiwi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:50:32 by mhotting          #+#    #+#             */
/*   Updated: 2024/06/17 18:47:12 by codekiwi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <errno.h>

#include "philo.h"

/**
 * @brief Waits for the monitor to be started
 * @param philo The philo who will wait for the monitor
 * @return true on SUCCESS, false on ERROR
 * @note if an error occured with the monitoring, errno will be set and make
 * the function fail
 */
static bool	philo_rout_wait_monitor(t_philo *philo)
{
	if (philo == NULL || philo->monitor == NULL)
		return (false);
	while (!t_monitoring_is_on(philo->monitor))
	{
		if (errno != 0 || !ft_usleep(10))
		{
			set_mutex_bool(philo->mutex_stop, philo->stopped, true);
			return (false);
		}
	}
	return (true);
}

/**
 * @brief Philo's routine initialization
 * 
 * Steps:
 * 	- locks/unlocks the start mutex in order to sync. the philo with the other
 * 	- if the philo's index is even, the philo will wait (sync.)
 * 	- if the number of philos is odd, the last philo will wait (sync.)
 * @param philo The philo whose routine will be started
 * @return true on SUCCESS, false on ERROR
 */
static bool	philo_routine_init(t_philo *philo)
{
	if (philo == NULL || pthread_mutex_lock(philo->mutex_start) != 0)
		return (false);
	if (pthread_mutex_unlock(philo->mutex_start) != 0)
		return (false);
	if (!philo_set_last_meal_start(philo))
	{
		set_mutex_bool(philo->mutex_stop, philo->stopped, true);
		return (false);
	}
	if (
		(philo->idx % 2 == 0 && !ft_msleep(philo->time_to_eat / 2))
		|| (philo->nb_philos % 2 != 0 && philo->idx == philo->nb_philos
			&& !ft_msleep(philo->time_to_eat))
	)
	{
		set_mutex_bool(philo->mutex_stop, philo->stopped, true);
		return (false);
	}
	return (true);
}

/**
 * @brief Philo's thread routine function
 * 
 * Initializes the philo before launching the routine loop
 * Then multiples steps: take forks, eat, sleep and think
 * After eating, if the number of meals requested has been reached, the
 * philo's finished flag is set to true (protected by a mutex)
 * In case of error, the loop is stopped and the meal stopped flag is
 * activated
 * @param philo_ptr A pointer to the philo whose routine is launched
 */
void	*philo_routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *) philo_ptr;
	if (!philo || !philo_rout_wait_monitor(philo) || !philo_routine_init(philo))
		return (NULL);
	while (true)
	{
		if (!philo_routine_forks(philo))
		{
			if (philo->nb_philos == 1)
				return (NULL);
			break ;
		}
		if (!philo_routine_eat(philo))
			break ;
		if (philo->nb_meals_limited && philo->nb_meals == philo->nb_meals_req)
		{
			if (!set_mutex_bool(philo->mutex_stop, &philo->finished, true))
				break ;
			return (NULL);
		}
		if (!philo_routine_sleep(philo) || !philo_routine_think(philo))
			break ;
	}
	return (set_mutex_bool(philo->mutex_stop, philo->stopped, true), NULL);
}

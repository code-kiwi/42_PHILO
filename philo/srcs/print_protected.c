/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pprint.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:52:32 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/23 16:55:05 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <pthread.h>

#include "philo.h"

/**
 * @brief Prints the action message for the given philo
 * 
 * The printing process checks the stop status of the given philo in order
 * to avoid displaying after the end of the meal
 * @param mutex_print The mutex that which protects the printing process
 * @param philo The philo whose action needs to be displayed
 * @return true in case of SUCCESS, false on ERROR
 */
bool	pprint(
	pthread_mutex_t *mutex_print, t_philo *philo,
	enum e_philo_action_type action
)
{
	int		ret;
	long	ts;
	bool	stopped;

	ts = philo_ts(philo);
	if (mutex_print == NULL || philo == NULL || ts == -1)
		return (false);
	if (pthread_mutex_lock(mutex_print) != 0)
		return (false);
	stopped = get_mutex_bool(philo->mutex_stop, philo->stopped);
	ret = 0;
	if (!stopped && action == ACT_FORK)
		ret = printf(LOG_MSG, ts, philo->idx, MSG_FORK);
	else if (!stopped && action == ACT_EAT)
		ret = printf(LOG_MSG, ts, philo->idx, MSG_EAT);
	else if (!stopped && action == ACT_SLEEP)
		ret = printf(LOG_MSG, ts, philo->idx, MSG_SLEEP);
	else if (!stopped && action == ACT_THINK)
		ret = printf(LOG_MSG, ts, philo->idx, MSG_THINK);
	if (pthread_mutex_unlock(mutex_print) != 0 || stopped || ret == -1)
		return (false);
	return (true);
}

/**
 * @brief Prints the death message for the given philo
 * @param mutex_print The mutex that which protects the printing process
 * @param philo The philo who dies
 * @return true in case of SUCCESS, false on ERROR
 */
bool	pprint_death(pthread_mutex_t *mutex_print, t_philo *philo)
{
	int		ret;
	long	ts;

	ts = philo_ts(philo);
	if (mutex_print == NULL || philo == NULL || ts == -1)
		return (false);
	if (pthread_mutex_lock(mutex_print) != 0)
		return (false);
	ret = printf(COL_RED LOG_MSG COL_RESET, ts, philo->idx, MSG_DIE);
	if (pthread_mutex_unlock(mutex_print) != 0 || ret == -1)
		return (false);
	return (true);
}

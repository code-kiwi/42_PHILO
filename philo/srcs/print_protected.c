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

bool	pprint(
	pthread_mutex_t *mutex_print, long ts,
	size_t idx, enum e_philo_action_type action
)
{
	int	ret;

	if (mutex_print == NULL || ts == -1)
		return (false);
	if (pthread_mutex_lock(mutex_print) != 0)
		return (false);
	if (action == ACT_FORK)
		ret = printf(LOG_MSG, ts, idx, MSG_FORK);
	else if (action == ACT_EAT)
		ret = printf(LOG_MSG, ts, idx, MSG_EAT);
	else if (action == ACT_SLEEP)
		ret = printf(LOG_MSG, ts, idx, MSG_SLEEP);
	else if (action == ACT_THINK)
		ret = printf(LOG_MSG, ts, idx, MSG_THINK);
	else if (action == ACT_DIE)
		ret = printf(LOG_MSG, ts, idx, MSG_DIE);
	if (pthread_mutex_unlock(mutex_print) != 0 || ret == -1)
		return (false);
	return (true);
}

// bool	pprint(
// 	pthread_mutex_t *mutex_print, long ts,
// 	size_t idx, enum e_philo_action_type action
// )
// {
// 	int	ret;

// 	if (mutex_print == NULL || ts == -1)
// 		return (false);
// 	if (pthread_mutex_lock(mutex_print) != 0)
// 		return (false);
// 	if (action == ACT_FORK)
// 		ret = printf(COL_YELLOW LOG_MSG COL_RESET, ts, idx, MSG_FORK);
// 	else if (action == ACT_EAT)
// 		ret = printf(COL_GREEN LOG_MSG COL_RESET, ts, idx, MSG_EAT);
// 	else if (action == ACT_SLEEP)
// 		ret = printf(COL_CYAN LOG_MSG COL_RESET, ts, idx, MSG_SLEEP);
// 	else if (action == ACT_THINK)
// 		ret = printf(COL_BLUE LOG_MSG COL_RESET, ts, idx, MSG_THINK);
// 	else if (action == ACT_DIE)
// 		ret = printf(COL_RED LOG_MSG COL_RESET, ts, idx, MSG_DIE);
// 	if (pthread_mutex_unlock(mutex_print) != 0 || ret == -1)
// 		return (false);
// 	return (true);
// }

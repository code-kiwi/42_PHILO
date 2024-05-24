/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:30:08 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/24 12:57:35 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>

#include "philo.h"

/**
 * @brief Returns the current timestamp in microseconds
 * @return The timestamp in microseconds, -1 in case of error
*/
long	get_current_timestamp(void)
{
	struct timeval	curr_time;

	if (gettimeofday(&curr_time, NULL) == -1)
		return (-1);
	return (curr_time.tv_sec * 1000000 + curr_time.tv_usec);
}

/**
 * @brief Returns the current timestamp in milliseconds
 * @return The timestamp in milliseconds, -1 in case of error
*/
long	get_ts(void)
{
	long	utime;

	utime = get_current_timestamp();
	if (utime == -1)
		return (-1);
	return (utime / 1000);
}

/**
 * 
*/
long	philo_ts(t_philo *philo)
{
	long	ts;

	if (philo == NULL)
		return (-1);
	ts = get_ts();
	if (ts == -1)
		return (-1);
	return (ts - philo->ts_initial);
}

/**
 * @brief Pauses the program during the given time
 * This function was created because of usleep lack of precision
 * 
 * @param time the time to pause, in microseconds
 * @return true if all went well, else returns false
*/
bool	ft_usleep(long time)
{
	long	remaining;
	long	elapsed;
	long	init_ts;
	long	curr_ts;

	init_ts = get_current_timestamp();
	if (init_ts == -1)
		return (false);
	remaining = time;
	elapsed = 0;
	while (elapsed < time)
	{
		curr_ts = get_current_timestamp();
		if (curr_ts == -1)
			return (false);
		elapsed = curr_ts - init_ts;
		remaining = elapsed - time;
		if (remaining > 1000)
		{
			if (usleep(remaining) == -1)
				return (false);
		}
	}
	return (true);
}

/**
 * @brief Pauses the program during the given time
 * @param time the time to pause, in milliseconds
 * @return true if all went well, else returns false
*/
bool	ft_msleep(size_t time)
{
	return (ft_usleep(time * 1000));
}

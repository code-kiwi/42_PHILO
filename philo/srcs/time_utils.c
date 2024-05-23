/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:30:08 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/23 16:28:01 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>

/**
 * @brief Returns a timestamp in microseconds, extracted from the given time
 * @param time Pointer to a timeval struct containing time info
 * @return The timestamp in microseconds, -1 in case of error
*/
long	get_timestamp(struct timeval *time)
{
	if (time == NULL)
		return (-1);
	return (time->tv_sec * 1000000 + time->tv_usec);
}

/**
 * @brief Returns the current timestamp in microseconds
 * @return The timestamp in microseconds, -1 in case of error
*/
long	get_current_timestamp(void)
{
	struct timeval	curr_time;

	if (gettimeofday(&curr_time, NULL) == -1)
		return (-1);
	return (get_timestamp(&curr_time));
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

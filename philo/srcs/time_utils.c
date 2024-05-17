/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:30:08 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/17 15:18:21 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>

/**
 * @brief Returns a timestamp in microseconds, extracted from the given time
 * @param time Pointer to a timeval struct containing time info
 * @return The timestamp in microseconds, -1 if the given pointer is NULL
*/
long	get_timestamp(struct timeval *time)
{
	if (time == NULL)
		return (-1);
	return (time->tv_sec * 1000000 + time->tv_usec);
}

/**
 * @brief Returns the current timestamp in microseconds
 * @return The timestamp in microseconds, -1 if the given pointer is NULL
*/
long	get_current_timestamp(void)
{
	struct timeval	curr_time;

	gettimeofday(&curr_time, NULL);
	return (get_timestamp(&curr_time));
}

/**
 * @brief Pauses the program during the given time
 * This function was created because of usleep lack of precision
 * 
 * @param time the time to pause, in microseconds
*/
void	ft_usleep(long time)
{
	long	remaining;
	long	elapsed;
	long	init_ts;

	init_ts = get_current_timestamp();
	remaining = time;
	elapsed = 0;
	while (elapsed < time)
	{
		elapsed = get_current_timestamp() - init_ts;
		remaining = elapsed - time;
		if (remaining > 1000)
			usleep(remaining);
	}
}

/**
 * @brief Pauses the program during the given time
 * @param time the time to pause, in milliseconds
*/
void	ft_msleep(size_t time)
{
	ft_usleep(time * 1000);
}

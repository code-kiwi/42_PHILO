/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:54:58 by mhotting          #+#    #+#             */
/*   Updated: 2024/06/10 16:14:54 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <pthread.h>

/**
 * @brief Returns the value of a boolean protected by a mutex
 * @param mutex The mutex which protects de variable
 * @param var_address The boolean variable address
 * @return true if the variable is true, false is it is false or if an error
 * occured (errno is then set according to pthread_mutex_lock/unlock)
*/
bool	get_mutex_bool(pthread_mutex_t *mutex, bool *var_addr)
{
	bool	ret;

	if (mutex == NULL || var_addr == NULL)
		return (false);
	if (pthread_mutex_lock(mutex) != 0)
		return (false);
	ret = *var_addr;
	if (pthread_mutex_unlock(mutex) != 0)
		return (false);
	return (ret);
}

/**
 * @brief Sets the value of a boolean variable protected by a mutex
 * @param mutex The mutex which protects de variable
 * @param var_address The boolean variable address
 * @param val the value to set
 * @return true on SUCCESS, false on ERROR
*/
bool	set_mutex_bool(
	pthread_mutex_t *mutex, bool *var_addr, bool val
)
{
	if (mutex == NULL || var_addr == NULL)
		return (false);
	if (pthread_mutex_lock(mutex) != 0)
		return (false);
	*var_addr = val;
	if (pthread_mutex_unlock(mutex) != 0)
		return (false);
	return (true);
}

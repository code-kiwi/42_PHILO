/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:54:58 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/31 14:02:14 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <pthread.h>

bool	get_mutex_protected_bool(pthread_mutex_t *mutex, bool *var_addr)
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

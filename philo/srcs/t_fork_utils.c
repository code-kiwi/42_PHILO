/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_fork_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:23:30 by mhotting          #+#    #+#             */
/*   Updated: 2024/06/10 15:38:34 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

#include "philo.h"

/**
 * @brief Initializes a t_fork, instantiates the given fork's mutex
 * @param fork The fork to initialize
 * @return true on SUCCESS, false on ERROR
*/
bool	t_fork_init(t_fork *fork)
{
	if (fork == NULL)
		return (false);
	fork->taken = false;
	if (pthread_mutex_init(&fork->mutex, NULL) != 0)
		return (false);
	return (true);
}

/**
 * @brief Destroys a t_fork
 * @param fork The fork to destroy
*/
void	t_fork_destroy(t_fork *fork)
{
	if (fork == NULL)
		return ;
	pthread_mutex_destroy(&fork->mutex);
}

/**
 * @brief Locks the given fork in order to consider it as taken
 * @param fork The fork to lock
 * @return true on SUCCESS, false on ERROR
*/
bool	t_fork_take(t_fork *fork)
{
	if (fork == NULL)
		return (false);
	if (pthread_mutex_lock(&fork->mutex) != 0)
		return (false);
	fork->taken = true;
	return (true);
}

/**
 * @brief Unlocks the given fork in order to consider it as put down
 * @param fork The fork to unlock
 * @return true on SUCCESS, false on ERROR
*/
bool	t_fork_put_down(t_fork *fork)
{
	if (fork == NULL)
		return (false);
	fork->taken = false;
	if (pthread_mutex_unlock(&fork->mutex) != 0)
		return (false);
	return (true);
}

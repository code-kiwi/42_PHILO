/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_fork_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:23:30 by mhotting          #+#    #+#             */
/*   Updated: 2024/06/10 14:06:34 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

#include "philo.h"

bool	t_fork_init(t_fork *fork)
{
	if (fork == NULL)
		return (false);
	fork->taken = false;
	if (pthread_mutex_init(&fork->mutex, NULL) != 0)
		return (false);
	return (true);
}

void	t_fork_destroy(t_fork *fork)
{
	if (fork == NULL)
		return ;
	pthread_mutex_destroy(&fork->mutex);
}

bool	t_fork_take(t_fork *fork)
{
	if (fork == NULL)
		return (false);
	if (pthread_mutex_lock(&fork->mutex) != 0)
		return (false);
	fork->taken = true;
	return (true);
}

bool	t_fork_put_down(t_fork *fork)
{
	if (fork == NULL)
		return (false);
	fork->taken = false;
	if (pthread_mutex_unlock(&fork->mutex) != 0)
		return (false);
	return (true);
}

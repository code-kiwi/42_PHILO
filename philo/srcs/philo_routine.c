/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:50:32 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/24 10:59:59 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

#include "philo.h"

static bool	philo_has_to_stop(t_philo *philo)
{
	return (philo == NULL || philo->is_dead || philo->has_dead_friend);
}

static bool	philo_routine_think(t_philo *philo)
{
	bool	ret;

	if (
		philo_has_to_stop(philo)
		|| !print_protected(philo->mutex_print, get_ts(), philo->idx, ACT_THINK)
	)
		return (false);
	if (pthread_mutex_lock(philo->left_fork) != 0)
		return (false);
	ret = print_protected(philo->mutex_print, get_ts(), philo->idx, ACT_FORK);
	if (!ret || pthread_mutex_lock(philo->right_fork) != 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		return (false);
	}
	if (!print_protected(philo->mutex_print, get_ts(), philo->idx, ACT_FORK))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (false);
	}
	return (true);
}

static bool	philo_routine_eat(t_philo *philo)
{
	bool	ret;
	long	timestamp;

	if (
		philo_has_to_stop(philo)
		|| !print_protected(philo->mutex_print, get_ts(), philo->idx, ACT_EAT)
	)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (false);
	}
	timestamp = get_ts();
	if (timestamp == -1)
		ret = false;
	philo->last_meal_start = timestamp;
	ret = ft_msleep(philo->time_to_eat) && ret;
	ret = (pthread_mutex_unlock(philo->left_fork) == 0) && ret;
	ret = (pthread_mutex_unlock(philo->right_fork) == 0) && ret;
	return (ret);
}

static bool	philo_routine_sleep(t_philo *philo)
{
	if (
		philo_has_to_stop(philo)
		|| !print_protected(philo->mutex_print, get_ts(), philo->idx, ACT_SLEEP)
		|| !ft_msleep(philo->time_to_sleep)
	)
		return (false);
	return (true);
}

void	*philo_routine(void *philo_ptr)
{
	t_philo	*philo;

	if (philo_ptr == NULL)
		return (NULL);
	philo = (t_philo *) philo_ptr;
	while (true)
	{
		if (!philo_routine_think(philo))
			break ;
		if (!philo_routine_eat(philo))
			break ;
		if (!philo_routine_sleep(philo))
			break ;
	}
	return (NULL);
}

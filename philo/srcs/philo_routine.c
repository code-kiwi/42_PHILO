/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:50:32 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/27 14:32:17 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>



#include <stdio.h>

#include "philo.h"

static bool	philo_routine_forks(t_philo *philo)
{
	if (philo->stopped || pthread_mutex_lock(philo->left_fork) != 0)
		return (false);
	if (
		!pprint(philo->mutex_print, philo_ts(philo), philo->idx, ACT_FORK)
		|| philo->stopped || pthread_mutex_lock(philo->right_fork) != 0
	)
	{
		pthread_mutex_unlock(philo->left_fork);
		return (false);
	}
	if (!pprint(philo->mutex_print, philo_ts(philo), philo->idx, ACT_FORK))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (false);
	}
	return (true);
}

static bool	philo_routine_think(t_philo *philo)
{
	if (
		philo->stopped
		|| !pprint(philo->mutex_print, philo_ts(philo), philo->idx, ACT_THINK)
	)
		return (false);
	return (true);
}

static bool	philo_routine_eat(t_philo *philo)
{
	bool	ret;

	if (
		philo->stopped
		|| !pprint(philo->mutex_print, philo_ts(philo), philo->idx, ACT_EAT)
	)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (false);
	}
	ret = true;
	philo->last_meal_start = get_ts();
	if (philo->last_meal_start == -1)
		ret = false;
	ret = ft_msleep(philo->time_to_eat) && ret;
	ret = (pthread_mutex_unlock(philo->left_fork) == 0) && ret;
	ret = (pthread_mutex_unlock(philo->right_fork) == 0) && ret;
	return (ret);
}

static bool	philo_routine_sleep(t_philo *philo)
{
	if (
		philo->stopped
		|| !pprint(philo->mutex_print, philo_ts(philo), philo->idx, ACT_SLEEP)
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
	if (pthread_mutex_lock(philo->mutex_start) != 0)
		return (NULL);
	philo->stopped = false;
	if (pthread_mutex_unlock(philo->mutex_start) != 0)
		return (NULL);
	if (philo->idx % 2 == 0)
		ft_msleep(philo->time_to_eat / 2);
	else if (philo->nb_philos % 2 != 0 && philo->idx == philo->nb_philos)
		ft_msleep(philo->time_to_eat);
	while (true)
	{
		if (!philo_routine_forks(philo))
		{
			printf("STOPPED FORK\n");
			break ;
		}
		if (!philo_routine_eat(philo))
		{
			printf("STOPPED FORK\n");
			break ;
		}
		if (!philo_routine_sleep(philo))
		{
			printf("STOPPED FORK\n");
			break ;
		}
		if (!philo_routine_think(philo))
		{
			printf("STOPPED FORK\n");
			break ;
		}
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_subroutines.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:50:32 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/28 23:44:35 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

#include "philo.h"

static void	philo_routine_forks_init(
	t_philo *philo, pthread_mutex_t **first_fork, pthread_mutex_t **second_fork
)
{
	if (philo->idx % 2 == 0)
	{
		*first_fork = philo->right_fork;
		*second_fork = philo->left_fork;
	}
	else
	{
		*first_fork = philo->left_fork;
		*second_fork = philo->right_fork;
	}
}

bool	philo_routine_forks(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (philo == NULL)
		return (false);
	philo_routine_forks_init(philo, &first_fork, &second_fork);
	if (philo->stopped || pthread_mutex_lock(first_fork) != 0)
		return (false);
	if (
		!pprint(philo->mutex_print, philo_ts(philo), philo->idx, ACT_FORK)
		|| philo->stopped || pthread_mutex_lock(second_fork) != 0
	)
	{
		pthread_mutex_unlock(first_fork);
		return (false);
	}
	if (!pprint(philo->mutex_print, philo_ts(philo), philo->idx, ACT_FORK))
	{
		pthread_mutex_unlock(first_fork);
		pthread_mutex_unlock(second_fork);
		return (false);
	}
	return (true);
}

bool	philo_routine_think(t_philo *philo)
{
	if (
		philo == NULL || philo->stopped
		|| !pprint(philo->mutex_print, philo_ts(philo), philo->idx, ACT_THINK)
	)
		return (false);
	return (true);
}

bool	philo_routine_eat(t_philo *philo)
{
	bool	ret;

	if (
		philo == NULL || philo->stopped
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
	philo->nb_meals_had += 1;
	return (ret);
}

bool	philo_routine_sleep(t_philo *philo)
{
	if (
		philo == NULL || philo->stopped
		|| !pprint(philo->mutex_print, philo_ts(philo), philo->idx, ACT_SLEEP)
		|| !ft_msleep(philo->time_to_sleep)
	)
		return (false);
	return (true);
}

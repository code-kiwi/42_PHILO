/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_philo_subroutines.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:50:32 by mhotting          #+#    #+#             */
/*   Updated: 2024/06/10 14:00:54 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

#include "philo.h"

static void	philo_routine_forks_init(
	t_philo *philo, t_fork **first_fork, t_fork **second_fork
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
	t_fork	*first_fork;
	t_fork	*second_fork;

	if (philo == NULL)
		return (false);
	philo_routine_forks_init(philo, &first_fork, &second_fork);
	if (!t_fork_take(first_fork))
		return (false);
	if (
		!pprint(philo->mutex_print, philo, ACT_FORK)
		|| !t_fork_take(second_fork)
	)
	{
		t_fork_put_down(first_fork);
		return (false);
	}
	if (!pprint(philo->mutex_print, philo, ACT_FORK))
	{
		t_fork_put_down(first_fork);
		t_fork_put_down(second_fork);
		return (false);
	}
	return (true);
}

bool	philo_routine_think(t_philo *philo)
{
	if (philo == NULL || !pprint(philo->mutex_print, philo, ACT_THINK))
		return (false);
	if (philo->nb_philos % 2 == 1 && philo->time_to_eat >= philo->time_to_sleep)
	{
		if (!ft_msleep(philo->time_to_eat))
			return (false);
	}
	return (true);
}

bool	philo_routine_eat(t_philo *philo)
{
	bool	ret;

	if (philo == NULL || !pprint(philo->mutex_print, philo, ACT_EAT))
	{
		t_fork_put_down(philo->left_fork);
		t_fork_put_down(philo->right_fork);
		return (false);
	}
	ret = true;
	if (!philo_set_last_meal_start(philo))
		ret = false;
	ret = ft_msleep(philo->time_to_eat) && ret;
	ret = t_fork_put_down(philo->left_fork) && ret;
	ret = t_fork_put_down(philo->right_fork) && ret;
	philo->nb_meals_had += 1;
	return (ret);
}

bool	philo_routine_sleep(t_philo *philo)
{
	if (
		philo == NULL || !pprint(philo->mutex_print, philo, ACT_SLEEP)
		|| !ft_msleep(philo->time_to_sleep)
	)
		return (false);
	return (true);
}

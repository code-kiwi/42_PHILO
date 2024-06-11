/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_philo_subroutines.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:50:32 by mhotting          #+#    #+#             */
/*   Updated: 2024/06/10 14:48:22 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

#include "philo.h"

/**
 * @brief Initializes the fork pointers with the right philo's forks
 * 
 * In order to avoid data races, odd philos will take the forks in an order
 * and the even philos will take them in the other order
 * @param philo The philo whose forks have to be selected
 * @param first_fork The pointer to the first fork to select
 * @param second_fork The pointer to the second fork to select
 */
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

/**
 * @brief Makes the given philo take both its forks
 * 
 * Takes both forks (protected by their mutexes)
 * Prints when they are taken (print protection by a mutex)
 * If the meal has stopped, the print will fail and the action will stop
 * @param philo The philo whose forks will be taken
 * @return true on SUCCESS, false on ERROR
 */
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

/**
 * @brief Makes the given philo think
 * 
 * Prints the think message (protected by print mutex)
 * If the meal has stopped, the print will fail
 * @param philo The philo who will think
 * @return true on SUCCESS, false on ERROR
 * @note The thinking process differs if there is an odd number of philos
 * In order to keep philos sync. the thinking process will consist of a meal_time
 * pause
 */
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

/**
 * @brief Makes the given philo eat
 * 
 * Prints the eat message (protected by print mutex)
 * Sets the new last meal time (mutex protection)
 * Sleeps time_to_eat milliseconds
 * Puts down the philo's forks (mutex protection)
 * Increases the number of meals
 * @param philo The philo whose forks will be taken
 * @return true on SUCCESS, false on ERROR
 */
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
	philo->nb_meals += 1;
	return (ret);
}

/**
 * @brief Makes the given philo sleep
 * 
 * Prints the sleep message (protected by print mutex)
 * Sleeps time_to_sleep milliseconds
 * @param philo The philo whose forks will be taken
 * @return true on SUCCESS, false on ERROR
 */
bool	philo_routine_sleep(t_philo *philo)
{
	if (
		philo == NULL || !pprint(philo->mutex_print, philo, ACT_SLEEP)
		|| !ft_msleep(philo->time_to_sleep)
	)
		return (false);
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_philo_data_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:37:40 by mhotting          #+#    #+#             */
/*   Updated: 2024/06/10 16:10:00 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "philo.h"

/**
 * @brief Destroys correctly and instance of t_philo_data
 * @param data a pointer to the instance to destroy
*/
void	data_destroy(t_philo_data *data)
{
	size_t	i;

	if (data == NULL)
		return ;
	if (data->philos != NULL)
	{
		free(data->philos);
		data->philos = NULL;
	}
	if (data->forks != NULL)
	{
		i = 0;
		while (i < data->nb_philos)
			t_fork_destroy(&data->forks[i++]);
		free(data->forks);
		data->forks = NULL;
	}
	pthread_mutex_destroy(&data->mutex_print);
	pthread_mutex_destroy(&data->mutex_start);
	pthread_mutex_destroy(&data->mutex_stop);
	pthread_mutex_destroy(&data->mutex_meal_time);
}

/**
 * @brief Join all the threads launched for the project
 * @param data The project's data address, where the threads are saved
 * @return true on SUCCESS, false on ERROR
*/
bool	data_join_threads(t_philo_data *data)
{
	size_t	i;
	bool	ret;

	if (data == NULL)
		return (false);
	ret = true;
	i = 0;
	while (i < data->nb_philos_launched)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			ret = false;
		i++;
	}
	if (
		data->monitor.thread_created
		&& pthread_join(data->monitor.thread, NULL) != 0
	)
		ret = false;
	return (ret);
}

/**
 * @brief Sets the given project's data members whose values are retrieved from
 * user inputs
 * @param data The project's data structure (its address) to affect
 * @param argc The number of arguments passed to the program
 * @param argv The arguments passed to the project
 * @return true on SUCCESS, false on ERROR
 * @note This functions prints an error message when an error is encountered
*/
static bool	data_init_from_params(t_philo_data *data, int argc, char **argv)
{
	if (data == NULL || argc < 5 || argc > 6 || argv == NULL)
		return (print_error(ERR_MSG_USAGE), false);
	if (!validate_args(argc, argv))
		return (print_error(ERR_MSG_PARAMS), false);
	data->nb_philos = ft_atoul(argv[1]);
	data->time_to_die = ft_atoul(argv[2]);
	data->time_to_eat = ft_atoul(argv[3]);
	data->time_to_sleep = ft_atoul(argv[4]);
	if (argc == 6)
	{
		data->nb_meals_req = ft_atoul(argv[5]);
		data->nb_meals_limited = true;
	}
	else
	{
		data->nb_meals_req = 0;
		data->nb_meals_limited = false;
	}
	return (true);
}

/**
 * @brief Initializes all the mutexes of the given project's data
 * @param data The project's data whose mutexes need to be initialized
 * @return true on SUCCESS, false on ERROR
*/
static bool	data_init_mutex(t_philo_data *data)
{
	pthread_mutex_t	*mutexes[4];
	size_t			i;

	mutexes[0] = &data->mutex_print;
	mutexes[1] = &data->mutex_start;
	mutexes[2] = &data->mutex_stop;
	mutexes[3] = &data->mutex_meal_time;
	i = 0;
	while (i < sizeof(mutexes) / sizeof(mutexes[0]))
	{
		if (pthread_mutex_init(mutexes[i], NULL) != 0)
		{
			while (i-- > 0)
				pthread_mutex_destroy(mutexes[i]);
			return (false);
		}
		i++;
	}
	return (true);
}

/**
 * @brief Initializes the given philo_data with the user input from argv
 * @param data a pointer to the t_philo_data structure to initialize
 * @param argc the number of arguments saved into argv
 * @param argv the arguments sent by the user
 * @return true if the initialization worked, else returns false
*/
bool	data_init(t_philo_data *data, int argc, char **argv)
{
	if (data == NULL)
		return (print_error(ERR_MSG_USAGE), false);
	memset(data, 0, sizeof(t_philo_data));
	if (!data_init_from_params(data, argc, argv))
		return (false);
	if (!data_init_mutex(data))
		return (false);
	return (true);
}

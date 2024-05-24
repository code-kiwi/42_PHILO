/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_philo_data_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:37:40 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/24 12:50:00 by mhotting         ###   ########.fr       */
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
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
		data->forks = NULL;
	}
	pthread_mutex_destroy(&data->mutex_print);
}

/**
 * @brief Initializes the given philo data with the user input from argv
 * @param data a pointer to the t_philo_data structure to initialize
 * @param argc the number of arguments saved into argv
 * @param argv the arguments sent by the user
 * @return true if the initialization worked, else returns false
*/
bool	data_init(t_philo_data *data, int argc, char **argv)
{
	if (data == NULL || argc < 5 || argc > 6 || argv == NULL)
		return (print_error(ERR_MSG_USAGE), false);
	if (!validate_args(argc, argv))
		return (print_error(ERR_MSG_PARAMS), false);
	memset(data, 0, sizeof(t_philo_data));
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
	if (pthread_mutex_init(&data->mutex_print, NULL) != 0)
		return (false);
	data->ts_initial = get_ts();
	if (data->ts_initial == -1)
		return (false);
	return (true);
}

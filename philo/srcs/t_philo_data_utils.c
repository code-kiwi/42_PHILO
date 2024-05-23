/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_philo_data_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:37:40 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/23 11:23:13 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>

#include "philo.h"

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
	{
		print_error(ERR_MSG_USAGE);
		return (false);
	}
	if (!validate_args(argc, argv))
	{
		print_error(ERR_MSG_PARAMS);
		return (false);
	}
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

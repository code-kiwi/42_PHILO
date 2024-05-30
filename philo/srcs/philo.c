/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:08:13 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/30 12:54:17 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo_data	data;
	bool			returned;

	if (!data_init(&data, argc, argv))
		return (EXIT_FAILURE);
	if (!create_project_elts(&data))
		return (EXIT_FAILURE);
	returned = launch_threads(&data);
	data_join_threads(&data);
	if (!returned)
	{
		data_destroy(&data);
		return (EXIT_FAILURE);
	}
	data_destroy(&data);
	return (0);
}

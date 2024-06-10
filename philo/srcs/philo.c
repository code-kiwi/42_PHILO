/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:08:13 by mhotting          #+#    #+#             */
/*   Updated: 2024/06/10 15:34:02 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

#include "philo.h"

/**
 * @brief Project's main function
 * 
 * Steps:
 * 	- creates data for the project
 * 	- creates the elements for running the project (forks and philos)
 * 	- launches the thread execution
 * 	- waits for each thread to end
 * 	- destroys the data
 * 	- returns status
*/
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
	data_destroy(&data);
	if (!returned)
		return (EXIT_FAILURE);
	return (0);
}

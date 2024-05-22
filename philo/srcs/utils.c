/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:35:03 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/22 16:57:08 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

#include "philo.h"

int	print_error(char *str)
{
	printf(ANSI_COL_RED "Error: " ANSI_RESET "%s\n", str);
	return (EXIT_FAILURE);
}
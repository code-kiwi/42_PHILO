/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_philo_data_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:37:40 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/22 17:00:18 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "philo.h"

bool    data_init(t_philo_data *data, int argc, char ** argv)
{
    if (data == NULL || argc < 5 || argc > 6 || argv == NULL)
        return (false);
    return (true);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:08:13 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/17 15:18:34 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "philo.h"

int	main(void)
{
	long	timestamp_init;
	long	timestamp_next;

	timestamp_init = get_current_timestamp();
	ft_usleep(1000000);
	timestamp_next = get_current_timestamp();
	printf("DIFF: %ld usec\n", timestamp_next - timestamp_init);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:08:13 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/11 11:04:09 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(void)
{
	struct timeval	curr_time;
	gettimeofday(&curr_time, NULL);
	printf("Seconds: %ld\nMicroseconds: %ld\n", curr_time.tv_sec, curr_time.tv_usec);
	return (0);
}

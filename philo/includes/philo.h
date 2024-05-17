/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:08:50 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/17 15:18:06 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>

// Time functions
long	get_timestamp(struct timeval *time);
long	get_current_timestamp(void);
void	ft_usleep(long time);
void	ft_msleep(size_t time);

#endif

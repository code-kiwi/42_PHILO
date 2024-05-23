/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:08:50 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/23 11:11:35 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdbool.h>
# include <sys/time.h>

# define ANSI_COL_RED		"\x1b[31m\x1b[1m"
# define ANSI_COL_BLUE		"\x1b[34m\x1b[1m"
# define ANSI_COL_GREEN		"\x1b[32m\x1b[1m"
# define ANSI_COL_CYAN		"\x1b[36m\x1b[1m"
# define ANSI_RESET			"\033[0m"

# define ERR_MSG_USAGE	\
	"Usage: philo nb_philos time_to_die time_to_eat time_to_sleep [nb_meals]"
# define ERR_MSG_PARAMS	"Args have to be positive numbers, lower than INTMAX"

typedef struct s_philo_data
{
	size_t	nb_philos;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	size_t	nb_meals_req;
	bool	nb_meals_limited;
}	t_philo_data;

// Time functions
long			get_timestamp(struct timeval *time);
long			get_current_timestamp(void);
void			ft_usleep(long time);
void			ft_msleep(size_t time);

// Philo data functions
bool			data_init(t_philo_data *data, int argc, char **argv);

// Validation functions
bool			validate_args(int argc, char **argv);

// Utils functions
unsigned long	ft_atoul(const char *nb_ptr);
int				ft_isdigit(int c);
int				ft_isspace(int c);
size_t			ft_strlen(const char *s);
void			print_error(char *str);

#endif

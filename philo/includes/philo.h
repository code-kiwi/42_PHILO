/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:08:50 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/23 16:54:19 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdbool.h>
# include <sys/time.h>
# include <pthread.h>

# define COL_RED	"\x1b[31m\x1b[1m"
# define COL_GREEN	"\x1b[32m\x1b[1m"
# define COL_YELLOW	"\x1b[33m\x1b[1m"
# define COL_BLUE	"\x1b[34m\x1b[1m"
# define COL_CYAN	"\x1b[36m\x1b[1m"
# define COL_RESET	"\033[0m"

# define MSG_FORK	"has taken a fork"
# define MSG_EAT	"is eating"
# define MSG_SLEEP	"is sleeping"
# define MSG_THINK	"is thinking"
# define MSG_DIE	"died"
# define LOG_MSG	"%ld %zu %s\n"

# define ERR_MSG_USAGE	\
	"Usage: philo nb_philos time_to_die time_to_eat time_to_sleep [nb_meals]"
# define ERR_MSG_PARAMS	"Args have to be positive numbers, lower than INTMAX"

typedef struct s_philo_data	t_philo_data;
typedef struct s_philo		t_philo;

struct s_philo_data
{
	size_t	nb_philos;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	size_t	nb_meals_req;
	bool	nb_meals_limited;
	t_philo	*philos;
};

struct s_philo
{
	size_t			idx;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*mutex_print;
	long			last_meal_start;
	bool			is_dead;
	bool			has_dead_friend;
	bool			stop_routine;
	long			time_to_eat;
	long			time_to_sleep;
};

enum e_philo_action_type
{
	ACT_FORK,
	ACT_EAT,
	ACT_SLEEP,
	ACT_THINK,
	ACT_DIE
};

// Time functions
long			get_timestamp(struct timeval *time);
long			get_current_timestamp(void);
long			get_ts(void);
bool			ft_usleep(long time);
bool			ft_msleep(size_t time);

// Philo data functions
bool			data_init(t_philo_data *data, int argc, char **argv);

// Philo functions
void			*philo_routine(void *philo_ptr);

// Validation functions
bool			validate_args(int argc, char **argv);

// Utils functions
unsigned long	ft_atoul(const char *nb_ptr);
int				ft_isdigit(int c);
int				ft_isspace(int c);
size_t			ft_strlen(const char *s);
void			print_error(char *str);
bool			print_protected(pthread_mutex_t *mutex_print, long ts, \
					size_t idx, enum e_philo_action_type action);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:08:50 by mhotting          #+#    #+#             */
/*   Updated: 2024/06/10 13:46:54 by mhotting         ###   ########.fr       */
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
# define COL_YELLOW	"\033[0;33m"
# define COL_BLUE	"\x1b[34m\x1b[1m"
# define COL_CYAN	"\x1b[36m\x1b[1m"
# define COL_RESET	"\033[0m"

# define MSG_FORK	"has taken a fork"
# define MSG_EAT	"is eating"
# define MSG_SLEEP	"is sleeping"
# define MSG_THINK	"is thinking"
# define MSG_DIE	"died"
// # define LOG_MSG	"%8ld %4zu %s\n"
# define LOG_MSG	"%ld %zu %s\n"

# define ERR_MSG_USAGE	\
	"Usage: philo nb_philos time_to_die time_to_eat time_to_sleep [nb_meals]"
# define ERR_MSG_PARAMS	"Args have to be positive numbers, lower than INT_MAX"

typedef struct s_philo_data		t_philo_data;
typedef struct s_philo			t_philo;
typedef struct s_fork			t_fork;
typedef struct s_monitor		t_monitor;

struct s_monitor
{
	pthread_t		thread;
	bool			thread_created;
	bool			started;
	bool			error;
	bool			nb_meals_limited;
	long			time_to_die;
	size_t			nb_philos;
	size_t			*nb_philos_launched;
	t_philo			*philos;
	pthread_mutex_t	mutex_monitor_start;
	pthread_mutex_t	mutex_error;
	pthread_mutex_t	*mutex_start;
	pthread_mutex_t	*mutex_print;
};

struct s_philo_data
{
	size_t			nb_philos;
	size_t			nb_philos_launched;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	size_t			nb_meals_req;
	bool			nb_meals_limited;
	bool			stopped;
	t_philo			*philos;
	t_fork			*forks;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	mutex_start;
	pthread_mutex_t	mutex_stop;
	pthread_mutex_t	mutex_meal_time;
	long			ts_initial;
	t_monitor		monitor;
};

struct s_philo
{
	size_t			idx;
	size_t			nb_philos;
	long			time_to_eat;
	long			time_to_sleep;
	long			last_meal_start;
	size_t			nb_meals_had;
	size_t			nb_meals_req;
	bool			nb_meals_limited;
	pthread_t		thread;
	bool			finished;
	bool			*stopped;
	size_t			*nb_philos_launched;
	long			*ts_initial;
	t_fork			*left_fork;
	t_fork			*right_fork;
	pthread_mutex_t	*mutex_meal_start;
	pthread_mutex_t	*mutex_stop;
	pthread_mutex_t	*mutex_print;
	pthread_mutex_t	*mutex_start;
	t_monitor		*monitor;
};

struct s_fork
{
	bool			taken;
	pthread_mutex_t	mutex;
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
long			get_current_timestamp(void);
long			get_ts(void);
long			philo_ts(t_philo *philo);
bool			ft_usleep(long time);
bool			ft_msleep(size_t time);

// Philo data functions
bool			data_init(t_philo_data *data, int argc, char **argv);
void			data_destroy(t_philo_data *data);
bool			create_project_elts(t_philo_data *data);
bool			data_join_threads(t_philo_data *data);

// Philo functions
bool			launch_threads(t_philo_data *data);
void			*philo_routine(void *philo_ptr);
bool			philo_routine_forks(t_philo *philo);
bool			philo_routine_think(t_philo *philo);
bool			philo_routine_eat(t_philo *philo);
bool			philo_routine_sleep(t_philo *philo);
bool			t_philo_init(t_philo *philo, t_philo_data *data, size_t index);
bool			philo_set_last_meal_start(t_philo *philo);
long			philo_get_last_meal_start(t_philo *philo);

// Validation functions
bool			validate_args(int argc, char **argv);

// Monitor functions
bool			t_monitor_init(t_monitor *monitor, t_philo_data *data);
bool			t_monitoring_is_on(t_monitor *monitor);
void			*t_monitor_routine(void *monitor_ptr);
bool			t_monitoring_set_error(t_monitor *monitor);
bool			t_monitoring_is_on_error(t_monitor *monitor);

// Fork functions
bool			t_fork_init(t_fork *fork);
void			t_fork_destroy(t_fork *fork);
bool			t_fork_take(t_fork *fork);
bool			t_fork_put_down(t_fork *fork);

// Utils functions
unsigned long	ft_atoul(const char *nb_ptr);
int				ft_isdigit(int c);
int				ft_isspace(int c);
size_t			ft_strlen(const char *s);
void			print_error(char *str);
bool			pprint(pthread_mutex_t *mutex_print, t_philo *philo, \
					enum e_philo_action_type action);
bool			pprint_death(pthread_mutex_t *mutex_print, t_philo *philo);
bool			get_mutex_bool(pthread_mutex_t *mutex, bool *var_add);
bool			set_mutex_bool(pthread_mutex_t *mutex, \
					bool *var_addr, bool val);

#endif

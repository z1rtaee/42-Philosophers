/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:27:51 by bpires-r          #+#    #+#             */
/*   Updated: 2025/07/22 18:46:12 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <sys/time.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <semaphore.h>

# define ERROR_ARG_NBR "Error: Wrong number of arguments.\n"
# define ERROR_INV_ARG "Error: Invalid arguments.\n"
# define ERROR_INIT "Error: failed to initialize data.\n"

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	int				ate;
	int				meals_eaten;
	long			last_meal;
	pid_t			pid;
	t_data			*data;
}				t_philo;

typedef struct s_data
{
	int				philos_nbr;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep; //how long they sleep after eat
	int				max_meals;
	int				stop;
	long			start_time;
	pid_t			*philo_ids;
	sem_t			*forks;
	sem_t			*print;
	sem_t			*meals_count;
	sem_t			*killer;
	pthread_mutex_t	data_lock;
	t_philo			*philos;
}				t_data;

//inits
int		init_data(t_data *data, char **argv);
int		init_philos(t_data *data);
int		init_semaphores(t_data *data);

//parser
int		is_valid_nbr(char *s);
int		check_args(char **argv);
int		parser_bonus(t_data *data, char **argv, int argc);

//free_exit_error
void	kill_all_philos(t_data *data);
void	kill_error(t_data *data, char *msg);
void	free_all(t_data *data);
void	free_resources(t_data *data);

//philo
void	*monitor(void *arg);
void	*meal_monitor(void *arg);
void	*philo_killer(void *arg);
void	*philo_routine(void *arg);
void	create_processes(t_data *data);
void	wait_processes(t_data *data);
void	lock_forks(t_philo *philo);
void	unlock_forks(t_philo *philo);

//utils
void	safe_print(t_data *data, t_philo *philo, char *msg);
void	sleep_ms(long ms);
long	get_time_ms(void);
long	ft_atol(char *s);

#endif
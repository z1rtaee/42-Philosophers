#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <sys/time.h>


# define ERROR_ARG_NBR "Error: Wrong number of arguments.\n"
# define ERROR_INV_ARG "Error: Invalid arguments.\n"
# define ERROR_INIT "Error: failed to initialize data\n"

typedef struct s_data t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}				t_philo;

typedef struct s_data
{
	int			philos_nbr;
	int			time_to_die; //max time a philo can go without eating
	int			time_to_eat; //how long a philo takes to eat
	int			time_to_sleep; //how long they sleep after eat
	int			max_meals;
	int			stop;
	long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	death_lock;
	t_philo			*philos;
}				t_data;

//Parser
int		check_args(char **argv);
int		init_data(t_data *data, char **argv);
int		init_philos(t_data	*data);
int		init_mutexes(t_data *data);

//Philo
void	*philo_routine(void *thread);
int		create_threads(t_data *data);
int		join_threads(t_data *data);
void	*monitor_routine(void *arg);


//Mutex Management
void	lock_forks(t_philo *philo);
void	unlock_forks(t_philo *philo);
void	barriguinha_cheia(t_philo *philo); 

//Utils
long	ft_atol(char *s);
void	print_action(t_philo *philo, char *msg);
void	sleep_ms(long ms);
long	get_time_ms(void);
int		all_philos_full(t_data *data);

//Memory Handle
void	free_all(t_data *data);
void	destroy_mutexes(t_data *data);

//ERROR
int		error_arg_nbr(void);
int		error_inv_arg(void);
int		error_init_failed(void);

#endif
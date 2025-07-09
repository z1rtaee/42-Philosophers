/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:27:51 by bpires-r          #+#    #+#             */
/*   Updated: 2025/07/09 23:13:46 by bpires-r         ###   ########.fr       */
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
# include <fcntl.h>
# include <semaphore.h>

# define ERROR_ARG_NBR "Error: Wrong number of arguments.\n"
# define ERROR_INV_ARG "Error: Invalid arguments.\n"
# define ERROR_INIT "Error: failed to initialize data.\n"

typedef struct s_data	t_data;

typedef struct s_philo 
{
	int		id;
	int		meals_eaten;
	long	last_meal;
	pid_t	pid;
	t_data	*data;
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
	t_philo			*philos;
}				t_data;

#endif
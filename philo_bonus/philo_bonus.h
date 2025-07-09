/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-09 18:27:51 by bpires-r          #+#    #+#             */
/*   Updated: 2025-07-09 18:27:51 by bpires-r         ###   ########.fr       */
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
# include <semaphore.h>

typedef struct s_data {
	int				philos_nbr;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep; //how long they sleep after eat
	int				max_meals;
	int				stop;
	long			start_time;
	pid_t			*philo_ids;
	sem_t			*forks;
	sem_t			*
}

#endif
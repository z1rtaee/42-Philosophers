/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c            ur                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:40:02 by bpires-r          #+#    #+#             */
/*   Updated: 2025/07/12 17:29:32 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitor(void *arg)
{
	t_philo	*philo;
	t_data 	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (1)
	{
		pthread_mutex_lock(&philo->death_lock);
		if (get_time_ms() - philo->last_meal > data->time_to_die)
		{
			sem_wait(data->print);
			printf("%ld %d died\n", get_time_ms() - data->start_time, philo->id);
			free_all(data);
			pthread_mutex_unlock(&philo->death_lock);
			exit(1);
		}
		pthread_mutex_unlock(&philo->death_lock);
		usleep(1000);
	}
	return (NULL);
}

void	safe_print(t_data *data, t_philo *philo, char *msg)
{
	sem_wait(data->print);
	print_action(philo, msg);
	sem_post(data->print);
}

void	*philo_routine(void *arg)
{
	t_philo		*philo;
	t_data		*data;
	pthread_t	monitor_thread;

	philo = (t_philo *)arg;
	data = philo->data;
	data->start_time = get_time_ms();
	philo->last_meal = data->start_time;
	pthread_create(&monitor_thread, NULL, monitor, philo);
	pthread_detach(monitor_thread);
	while (1)
	{
		lock_forks(philo);
		pthread_mutex_lock(&philo->death_lock);
		philo->last_meal = get_time_ms();
		pthread_mutex_unlock(&philo->death_lock);
		safe_print(data, philo, "is eating");
		pthread_mutex_lock(&philo->death_lock);
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->death_lock);
		sleep_ms(data->time_to_eat);
		unlock_forks(philo);
		safe_print(data, philo, "is sleeping");
		sleep_ms(data->time_to_sleep);
		safe_print(data, philo, "is thinking");
		usleep(100);
	}
	return (NULL);
}

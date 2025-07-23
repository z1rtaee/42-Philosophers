/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 18:47:23 by bpires-r          #+#    #+#             */
/*   Updated: 2025/07/22 18:49:36 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitor(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (1)
	{
		pthread_mutex_lock(&data->data_lock);
		if (philo->ate)
		{
			pthread_mutex_unlock(&data->data_lock);
			break ;
		}
		if (get_time_ms() - philo->last_meal > data->time_to_die)
		{
			pthread_mutex_unlock(&data->data_lock);
			sem_wait(data->print);
			printf("%ld %d died\n",
				get_time_ms() - data->start_time, philo->id);
			return (sem_post(data->killer), NULL);
		}
		pthread_mutex_unlock(&data->data_lock);
		usleep(1000);
	}
	return (NULL);
}

void	*meal_monitor(void *arg)
{
	t_data	*data;
	int		i;

	i = 0;
	data = (t_data *)arg;
	while (i < data->philos_nbr)
	{
		pthread_mutex_lock(&data->data_lock);
		if (data->stop)
		{
			pthread_mutex_unlock(&data->data_lock);
			return (NULL);
		}
		pthread_mutex_unlock(&data->data_lock);
		sem_wait(data->meals_count);
		i++;
	}
	pthread_mutex_lock(&data->data_lock);
	data->stop = 1;
	pthread_mutex_unlock(&data->data_lock);
	sem_post(data->killer);
	sem_wait(data->print);
	printf("All philosophers have eaten %d times.\n", data->max_meals);
	sem_post(data->print);
	return (NULL);
}

void	*philo_killer(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	sem_wait(data->killer);
	pthread_mutex_lock(&data->data_lock);
	if (data->stop)
	{
		pthread_mutex_unlock(&data->data_lock);
		return (NULL);
	}
	pthread_mutex_unlock(&data->data_lock);
	if (data->max_meals > 0)
	{
		pthread_mutex_lock(&data->data_lock);
		data->stop = 1;
		pthread_mutex_unlock(&data->data_lock);
		sem_post(data->meals_count);
	}
	pthread_mutex_lock(&data->data_lock);
	kill_all_philos(data);
	pthread_mutex_unlock(&data->data_lock);
	return (NULL);
}

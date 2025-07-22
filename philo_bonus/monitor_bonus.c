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
		pthread_mutex_lock(&philo->death_lock);
		if (philo->ate)
		{
			pthread_mutex_unlock(&philo->death_lock);
			break ;
		}
		if (get_time_ms() - philo->last_meal > data->time_to_die)
		{
			sem_wait(data->print);
			printf("%ld %d died\n",
				get_time_ms() - data->start_time, philo->id);
			pthread_mutex_unlock(&philo->death_lock);
			return (sem_post(data->killer), NULL);
		}
		pthread_mutex_unlock(&philo->death_lock);
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
		if (data->stop)
			return (NULL);
		sem_wait(data->meals_count);
		i++;
	}
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
	if (data->max_meals > 0)
	{
		data->stop = 1;
		sem_post(data->meals_count);
	}
	kill_all_philos(data);
	return (NULL);
}

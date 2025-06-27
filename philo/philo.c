/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 20:12:25 by bpires-r          #+#    #+#             */
/*   Updated: 2025/06/26 22:44:57 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	simulation_end(t_philo *philo)
{
	int	stop;

	pthread_mutex_lock(&philo->data->death_lock);
	stop = philo->data->stop;
	pthread_mutex_unlock(&philo->data->death_lock);
	return (stop);
}

int	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_nbr)
	{
		if (pthread_join(data->philos[i].thread, NULL))
			return (0);
		i++;
	}
	return (1);
}

int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->death_lock);
	data->start_time = get_time_ms();
	while (i < data->philos_nbr)
	{
		data->philos[i].last_meal = data->start_time;
		if (pthread_create(&data->philos[i].thread, NULL, philo_routine, &data->philos[i]))
			return (0);
		i++;
	}
	return (1);
}

void	*philo_routine(void *thread)
{
	t_philo	*philo;

	philo = (t_philo *)thread;
	if (philo->id % 2 == 0)
		usleep(100);
	while (!simulation_end(philo))
	{
		if (philo->data->philos_nbr == 1)
		{
			pthread_mutex_lock(philo->left_fork);
			print_action(philo, "has taken a fork");
			sleep_ms(philo->data->time_to_die);
			print_action(philo, "died");
			pthread_mutex_unlock(philo->left_fork);
			philo->data->stop = 1;
			return (NULL);
		}
		lock_forks(philo);
		barriguinha_cheia(philo);
		unlock_forks(philo);
		print_action(philo, "is sleeping");
		sleep_ms(philo->data->time_to_sleep);
		print_action(philo, "is thinking");
	}
	return (NULL);
}
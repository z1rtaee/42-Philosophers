/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:05:25 by bpires-r          #+#    #+#             */
/*   Updated: 2025/07/22 18:53:33 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	routine_loop(t_philo *philo, t_data *data)
{
	while (1)
	{
		lock_forks(philo);
		pthread_mutex_lock(&philo->death_lock);
		philo->last_meal = get_time_ms();
		pthread_mutex_unlock(&philo->death_lock);
		safe_print(data, philo, "is eating");
		pthread_mutex_lock(&philo->death_lock);
		philo->meals_eaten++;
		if (data->max_meals == philo->meals_eaten)
		{
			philo->ate = 1;
			sem_post(data->meals_count);
			pthread_mutex_unlock(&philo->death_lock);
			unlock_forks(philo);
			break ;
		}
		pthread_mutex_unlock(&philo->death_lock);
		sleep_ms(data->time_to_eat);
		unlock_forks(philo);
		safe_print(data, philo, "is sleeping");
		sleep_ms(data->time_to_sleep);
		safe_print(data, philo, "is thinking");
		usleep(100);
	}
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
	if (philo->id % 2)
		usleep(100);
	routine_loop(philo, data);
	return (NULL);
}

void	wait_processes(t_data *data)
{
	int		i;

	if (!data->max_meals)
	{
		if (waitpid(-1, NULL, 0))
			return ;
	}
	i = 0;
	while (i < data->philos_nbr)
	{
		waitpid(data->philo_ids[i], NULL, 0);
		i++;
	}
}

void	create_processes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_nbr)
	{
		data->philo_ids[i] = fork();
		if (data->philo_ids[i] == -1)
		{
			kill_error(data, "Error: Failed to create child process.");
			free_all(data);
			exit(1);
		}
		else if (data->philo_ids[i] == 0)
		{
			philo_routine(&data->philos[i]);
			free_all(data);
			exit(0);
		}
		i++;
	}
}

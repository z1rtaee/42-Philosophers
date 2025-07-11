/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 21:56:22 by bpires-r          #+#    #+#             */
/*   Updated: 2025/07/05 20:11:13 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		check_death(data);
		if (data->stop)
			return (NULL);
		pthread_mutex_lock(&data->death_lock);
		if (data->max_meals > 0 && all_philos_full(data))
		{
			data->stop = 1;
			pthread_mutex_unlock(&data->death_lock);
			return (NULL);
		}
		pthread_mutex_unlock(&data->death_lock);
		usleep(1000);
	}
}

void	check_death(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_nbr)
	{
		pthread_mutex_lock(&data->death_lock);
		if ((get_time_ms() - data->philos[i].last_meal) > data->time_to_die)
		{
			pthread_mutex_unlock(&data->death_lock);
			print_action(&data->philos[i], "died");
			pthread_mutex_lock(&data->death_lock);
			data->stop = 1;
			pthread_mutex_unlock(&data->death_lock);
			return ;
		}
		pthread_mutex_unlock(&data->death_lock);
		i++;
	}
}

int	all_philos_full(t_data *data)
{
	int	i;
	int	full;

	i = 0;
	full = 1;
	while (i < data->philos_nbr)
	{
		if (data->philos[i].meals_eaten < data->max_meals)
		{
			full = 0;
			break ;
		}
		i++;
	}
	return (full);
}

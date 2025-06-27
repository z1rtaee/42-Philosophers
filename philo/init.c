/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:41:10 by bpires-r          #+#    #+#             */
/*   Updated: 2025/06/26 20:09:52 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data *data, char **argv)
{
	data->philos_nbr = (int)ft_atol(argv[1]);
	data->time_to_die = (int)ft_atol(argv[2]);
	data->time_to_eat = (int)ft_atol(argv[3]);
	data->time_to_sleep = (int)ft_atol(argv[4]);
	data->stop = 0;
	data->start_time = 0;
	data->philos = malloc(sizeof(t_philo) * data->philos_nbr);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philos_nbr);
	if (!data->philos || !data->forks)
		return (0);
	if (argv[5])
		data->max_meals = (int)ft_atol(argv[5]);
	else
		data->max_meals = -1;
	return (1);
}

int	init_philos(t_data	*data)
{
	int	i;

	i = 0;
	while (i < data->philos_nbr)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal = 0;
		data->philos[i].data = data;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->philos_nbr];
		i++;
	}
	return (1);
}

int	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&data->death_lock, NULL))
		return (0);
	if (pthread_mutex_init(&data->print_lock, NULL))
		return (0);
	while (i <data->philos_nbr)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (0);
		i++;
	}
	return (1);
}

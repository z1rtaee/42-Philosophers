/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 23:04:32 by bpires-r          #+#    #+#             */
/*   Updated: 2025/07/22 18:47:57 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_data(t_data *data, char **argv)
{
	data->philos_nbr = ft_atol(argv[1]);
	data->time_to_die = (int)ft_atol(argv[2]);
	data->time_to_eat = (int)ft_atol(argv[3]);
	data->time_to_sleep = (int)ft_atol(argv[4]);
	data->stop = 0;
	data->philos = malloc(sizeof(t_philo) * data->philos_nbr);
	if (!data->philos)
		return (0);
	if (argv[5])
		data->max_meals = (int)ft_atol(argv[5]);
	else
		data->max_meals = 0;
	data->philo_ids = malloc(sizeof(pid_t) * data->philos_nbr);
	if (!data->philo_ids)
		return (0);
	pthread_mutex_init(&data->data_lock, NULL);
	return (1);
}

int	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_nbr)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal = 0;
		data->philos[i].data = data;
		data->philos[i].ate = 0;
		i++;
	}
	return (1);
}

int	init_semaphores(t_data *data)
{
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/meals_count");
	sem_unlink("/killer");
	data->forks = sem_open("/forks", O_CREAT | O_EXCL, S_IWUSR,
			data->philos_nbr);
	data->print = sem_open("/print", O_CREAT | O_EXCL, S_IWUSR, 1);
	data->meals_count = sem_open("/meals_count", O_CREAT | O_EXCL, S_IWUSR, 0);
	data->killer = sem_open("/killer", O_CREAT | O_EXCL, S_IWUSR, 0);
	if (data->forks == SEM_FAILED || data->print == SEM_FAILED
		|| data->meals_count == SEM_FAILED || data->killer == SEM_FAILED)
		return (0);
	return (1);
}

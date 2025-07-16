/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit_error_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 23:21:30 by bpires-r          #+#    #+#             */
/*   Updated: 2025/07/15 19:44:50 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	kill_all_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_nbr)
	{
		kill(data->philo_ids[i], SIGKILL);
		i++;
	}
}

void	kill_error(t_data *data, char *msg)
{
	int	i;

	i = 0;
	while (msg && msg[i])
	{
		write(2, &msg[i], 1);
		i++;
	}
	kill_all_philos(data);
	return ;
}

void	free_all(t_data *data)
{
	free_resources(data);
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/meals_count");
}

void	free_resources(t_data *data)
{
	if (data->philos)
		free(data->philos);
	if (data->philo_ids)
		free(data->philo_ids);
	if (data->forks != NULL && data->forks != SEM_FAILED)
		sem_close(data->forks);
	if (data->print != NULL && data->print != SEM_FAILED)
		sem_close(data->print);
	if (data->meals_count != NULL && data->meals_count != SEM_FAILED)
		sem_close(data->meals_count);
}

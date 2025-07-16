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
		kill(data->philos[i].pid, SIGKILL);
		i++;
	}
}

void	kill_error(t_data *data, char *msg)
{
	int	i;

	i = 0;
	while (msg)
	{
		write(2, &msg[i], 1);
		i++;
	}
	kill_all_philos(data);
	return ;
}

void	free_all(t_data *data)
{
	if (data->philos)
		free(data->philos);
	if (data->forks != SEM_FAILED && data->forks != NULL)
	{
		sem_close(data->forks);
		sem_unlink("/forks");
	}
	if (data->print != SEM_FAILED && data->print != NULL)
	{
		sem_close(data->print);
		sem_unlink("/print");
	}
}

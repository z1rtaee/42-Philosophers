/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:05:25 by bpires-r          #+#    #+#             */
/*   Updated: 2025/07/12 18:06:01 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	wait_processes(t_data *data)
{
	int		status;
	pid_t	pid;

	status = 0;
	pid = waitpid(-1, &status, 0);
	if (pid > 0)
		kill_all_philos(data);
	while (waitpid(-1, NULL, 0) > 0)
		;
}

void	create_processes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_nbr)
	{
		data->philos[i].pid = fork();
		if (data->philos[i].pid == -1)
		{
			kill_error(data, "Error: Failed to create child process.");
			free_all(data);
			exit(1);
		}
		else if (data->philos[i].pid == 0)
		{
			philo_routine(&data->philos[i]);
			exit(0);
		}
		i++;
	}
}

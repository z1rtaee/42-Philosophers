/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 21:08:55 by bpires-r          #+#    #+#             */
/*   Updated: 2025/07/05 20:12:26 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_arg_nbr(void)
{
	printf(ERROR_ARG_NBR);
	return (1);
}

int	error_inv_arg(void)
{
	printf(ERROR_INV_ARG);
	return (1);
}

int	error_init_failed(void)
{
	printf(ERROR_INIT);
	return (1);
}

void	destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->death_lock);
	while (i < data->philos_nbr)
		pthread_mutex_destroy(&data->forks[i++]);
}

void	free_all(t_data *data)
{
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
}

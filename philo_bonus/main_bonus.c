/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 22:59:03 by bpires-r          #+#    #+#             */
/*   Updated: 2025/07/22 18:45:20 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	meal_thread;
	pthread_t	death_thread;

	if (!parser_bonus(&data, argv, argc))
		return (1);
	create_processes(&data);
	if (data.max_meals > 0)
	{
		pthread_create(&meal_thread, NULL, meal_monitor, &data);
		pthread_detach(meal_thread);
	}
	pthread_create(&death_thread, NULL, philo_killer, &data);
	pthread_detach(death_thread);
	wait_processes(&data);
	pthread_mutex_lock(&data.data_lock);
	free_all(&data);
	pthread_mutex_unlock(&data.data_lock);
	pthread_mutex_destroy(&data.data_lock);
	return (0);
}

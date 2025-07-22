/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 22:59:03 by bpires-r          #+#    #+#             */
/*   Updated: 2025/07/22 17:48:41 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int main(int argc, char **argv)
{
	t_data	data;
	pthread_t	meal_thread;
	pthread_t	death_thread;

	if (argc < 5 || argc > 6)
	{
		printf(ERROR_ARG_NBR);
		return (1);
	}
	if (!check_args(argv))
	{
		printf(ERROR_INV_ARG);
		return (1);
	}
	if (!init_data(&data, argv) || !init_philos(&data)
		|| !init_semaphores(&data))
	{
		printf(ERROR_INIT); 
		return (1);
	}
	create_processes(&data);
	if (data.max_meals > 0)
	{
		pthread_create(&meal_thread, NULL, meal_monitor, &data);
		pthread_detach(meal_thread);
	}
	pthread_create(&death_thread, NULL, philo_killer, &data);
	pthread_detach(death_thread);
	wait_processes(&data);
	free_all(&data);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:01:08 by bpires-r          #+#    #+#             */
/*   Updated: 2025/06/30 16:39:22 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	monitor;

	if (argc < 5 || argc > 6)
		return (error_arg_nbr());
	if (!check_args(argv))
		return (error_inv_arg());
	if (!init_data(&data, argv) || !init_mutexes(&data)
		|| !init_philos(&data) || !create_threads(&data))
			return (error_init_failed());
	if (pthread_create(&monitor, NULL, monitor_routine, &data))
		return (error_init_failed());
	pthread_mutex_unlock(&data.death_lock);
	pthread_join(monitor, NULL);
	if (!join_threads(&data))
		return (error_init_failed());
	destroy_mutexes(&data);
	free_all(&data);
	return (0);
}

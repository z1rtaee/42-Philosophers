/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 22:59:03 by bpires-r          #+#    #+#             */
/*   Updated: 2025/07/09 23:04:09 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int main(int argc, char **argv)
{
    t_data  data;

	if (argc < 5 || argc > 6)
		return (error_arg_nbr());
	if (!check_args(argv))
		return (error_inv_arg());
	if (!init_data(&data, argv) || !init_mutexes(&data)
		|| !init_philos(&data) || !create_threads(&data))
		return (error_init_failed());
    start_simulation(&data);
    free_all(&data);
    return (0);
}

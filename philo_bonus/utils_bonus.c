/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 23:01:38 by bpires-r          #+#    #+#             */
/*   Updated: 2025/07/22 18:50:24 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	sleep_ms(long ms)
{
	usleep(ms * 1000);
}

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	safe_print(t_data *data, t_philo *philo, char *msg)
{
	sem_wait(data->print);
	printf("%ld %d %s\n",
		get_time_ms() - philo->data->start_time, philo->id, msg);
	sem_post(data->print);
}

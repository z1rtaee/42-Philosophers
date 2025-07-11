/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 20:23:24 by bpires-r          #+#    #+#             */
/*   Updated: 2025/07/05 19:47:25 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_philo *philo, char *msg)
{
	long	time_stamp;

	pthread_mutex_lock(&philo->data->death_lock);
	if (!philo->data->stop)
	{
		time_stamp = get_time_ms() - philo->data->start_time;
		printf("%ld %d %s\n", time_stamp, philo->id, msg);
		pthread_mutex_unlock(&philo->data->death_lock);
	}
	else
		pthread_mutex_unlock(&philo->data->death_lock);
}

void	sleep_ms(long ms)
{
	long	start;

	start = get_time_ms();
	while ((get_time_ms() - start) < ms)
		usleep(500);
}

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

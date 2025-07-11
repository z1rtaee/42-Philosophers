/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 20:40:35 by bpires-r          #+#    #+#             */
/*   Updated: 2025/07/05 19:46:23 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
	}
}

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	barriguinha_cheia(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_lock);
	if (philo->data->stop)
	{
		pthread_mutex_unlock(&philo->data->death_lock);
		return ;
	}
	philo->last_meal = get_time_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->death_lock);
	print_action(philo, "is eating");
	sleep_ms(philo->data->time_to_eat);
}

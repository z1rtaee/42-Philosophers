/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 18:33:50 by bpires-r          #+#    #+#             */
/*   Updated: 2025/07/16 16:56:46 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	lock_forks(t_philo *philo)
{
	sem_wait(philo->data->forks);
	safe_print(philo->data, philo, "has taken a fork");
	sem_wait(philo->data->forks);
	safe_print(philo->data, philo, "has taken a fork");
}

void	unlock_forks(t_philo *philo)
{
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

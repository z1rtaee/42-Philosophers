/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 23:02:26 by bpires-r          #+#    #+#             */
/*   Updated: 2025/07/09 23:02:44 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	ft_atol(char *s)
{
	long	res;
	int		i;

	res = 0;
	i = 0;
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] == '+')
		i++;
	while (s[i] >= '0' && s[i] <= '9')
	{
		res = res * 10 + (s[i] - '0');
		i++;
	}
	return (res);
}

int	is_valid_nbr(char *s)
{
	int	i;

	i = 0;
	if (!s || !s[0])
		return (0);
	if (s[0] == '+')
		i++;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	check_args(char **argv)
{
	long	nb;
	int		i;

	i = 1;
	while (argv[i])
	{
		if (!is_valid_nbr(argv[i]))
			return (0);
		nb = ft_atol(argv[i]);
		if (nb <= 0 || nb > __INT_MAX__)
			return (0);
		i++;
	}
	return (1);
}

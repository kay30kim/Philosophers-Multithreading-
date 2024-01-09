/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kay <kay@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:57:15 by kay               #+#    #+#             */
/*   Updated: 2024/01/09 12:32:47 by kay              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_numcheck(const char *str)
{
	int		i;

	i = 0;
	if (!str || str[i] == '\0' || str[i] == '0')
		return (1);
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] != '\0')
		return (1);
	return (0);
}

size_t	ft_atol(char* str)
{
	int	i;
	size_t num;

	i = 0;
	if (!str || str[i] == '\0')
		return (0);
	num = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		num = num * 10 + (str[i++] - '0');
	if (str[i] != '\0')
		return (1);
	return (num);
}
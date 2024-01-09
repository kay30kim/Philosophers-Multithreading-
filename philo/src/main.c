/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kay <kay@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 15:59:17 by kay               #+#    #+#             */
/*   Updated: 2024/01/09 13:06:32 by kay              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int argu_check(t_info *info, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (1);
	if (ft_numcheck(argv[1]) ||
		ft_numcheck(argv[2]) ||
		ft_numcheck(argv[3]) ||
		ft_numcheck(argv[4]))
		return (1);
	if (argc == 6 && (ft_numcheck(argv[5])))
		return (1);
	return (0);
}

int init_arg(t_info *info, int argc, char **argv)
{
	info->n_mans = ft_atol(argv[1]);
	info->time_die = ft_atol(argv[2]);
	info->time_eat = ft_atol(argv[3]);
	info->time_sleep = ft_atol(argv[4]);
	if (argc == 6)
		info->n_must_eat = ft_atol(argv[5]);
	else if (argc == 5)
		info->n_must_eat = -1;
	info->finish = 0;
	return (0);
}

int	init_man(t_info *info)
{
	int	i;

	info->mans = malloc(sizeof(t_man) * info->n_mans);
	if (!info->mans)
		return (1);
	info->forks = malloc(sizeof(int) * info->n_mans);
	if (!info->forks)
		return (1);
	i = 0;
	while (i < info->n_mans)
	{
		info->forks[i] = 0;
		info->mans[i].pos = i;
		info->mans[i].left_fork = i;
		info->mans[i].right_fork = (i + 1) % info->n_mans;
		info->mans[i].nfoods = 0;
		info->mans[i].iseat = 0;
		info->mans[i].instance = info;
		i++;
	}
	return (0);
}

int	init_mutex(t_info *info)
{
	int	i;

	info->mutexes = malloc(sizeof(pthread_mutex_t)
						* info->n_mans);
	if (!info->mutexes)
		return (1);
	i = 0;
	while (i < info->n_mans)
		pthread_mutex_init(&info->mutexes[i++], NULL);
	ptrhead_mutex_init(&info->write_mutex, NULL);
	pthread_mutex_init(&info->die_mutex, NULL);
	return (0);
}

void	destroy_mutex_free_malloc(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->n_mans)
	{
		pthread_mutex_destroy(&info->mutexes[i]);
		i++;
	}
	pthread_mutex_destroy(&info->write_mutex);
	pthread_mutex_destroy(&info->die_mutex);
	free(info->mutexes);
	free(info->mans);
	free(info->forks);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (argu_check(&info, argc, argv))
		return (1);

	if (init_arg(&info, argc, argv)
		|| init_man(&info)
		|| init_mutex(&info))
		return (1);
	if (go(&info))
		return (1);
	pthread_mutex_lock(&info.die_mutex);
	pthread_mutex_unlock(&info.die_mutex);
	destroy_mutex_free_malloc(&info);
	return (0);
}

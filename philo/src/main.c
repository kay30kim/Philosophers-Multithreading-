/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kay <kay@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 15:59:17 by kay               #+#    #+#             */
/*   Updated: 2024/03/25 15:28:44 by kay              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	argu_check(int argc, char **argv)
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

int	init_arg(t_info *info, int argc, char **argv)
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

int	free_man(t_info *info)
{
	free(info->mans);
	return (1);
}

int	free_info(t_info *info)
{
	free(info->mans);
	free(info->forks);
	return (1);
}

int	init_man(t_info *info)
{
	int	i;

	info->mans = malloc(sizeof(t_man) * info->n_mans);
	if (!info->mans)
		return (free_man(info));
	info->forks = malloc(sizeof(int) * info->n_mans);
	info->start_time = get_time();
	if (!info->forks)
		return (free_info(info));
	i = 0;
	while (i < info->n_mans)
	{
		info->mans[i].id = i + 1;
		info->mans[i].left_fork = i;
		info->mans[i].right_fork = (i + 1) % info->n_mans;
		info->mans[i].eat_cnt = 0;
		info->mans[i].last_eat_time = info->start_time;
		info->mans[i].info = info;
		i++;
	}
	return (0);
}

int	free_destroy_init(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->n_mans)
		pthread_mutex_destroy(&info->forks[i]);
	free_info(info);
	pthread_mutex_destroy(&info->print_mutex);
	pthread_mutex_destroy(&info->eat_mutex);
	return (0);
}

int	free_destroy(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->n_mans)
		pthread_mutex_destroy(&info->forks[i]);
	free_info(info);
	pthread_mutex_destroy(&info->print_mutex);
	pthread_mutex_destroy(&info->eat_mutex);
	pthread_mutex_destroy(&info->finish_mutex);
	return (0);
}

int	init_mutex(t_info *info)
{
	int	i;
	int	j;

	i = 0;
	(void)j;
	j = -1;
	while (i < info->n_mans)
	{
		if (pthread_mutex_init(&info->forks[i++], NULL))
		{
			while (++j < i)
				pthread_mutex_destroy(&info->forks[i]);
			free_info(info);
			return (print_err("Init forks mutex fails\n"));
		}
	}
	if (pthread_mutex_init(&info->eat_mutex, NULL))
		return (free_destroy_init(info));
	if (pthread_mutex_init(&info->finish_mutex, NULL))
		return (free_destroy(info));
	return (0);
}
int	isdead(t_man *philo)
{
	pthread_mutex_lock(&philo->info->eat_mutex);
	if ((get_time() - philo->last_eat_time) >= philo->info->time_die)
	{
		print(philo, "died");
		done(philo);
		pthread_mutex_unlock(&philo->info->eat_mutex);
		return (1);
	}
	else if (philo->info->n_must_eat > 0 && philo->eat_cnt >= \
			philo->info->n_must_eat)
	{
		philo->info->n_full_man++;
		if (philo->info->n_full_man >= philo->info->n_mans)
		{
			done(philo);
			print(philo, "success");
			pthread_mutex_unlock(&philo->info->eat_mutex);
			return (1);
		}
	}
	pthread_mutex_unlock(&philo->info->eat_mutex);
	return (0);
}

void	destroy(t_info *info)
{
	int	i;
	int	flag;

	flag = 1;
	while (flag)
	{
		i = -1;
		info->n_full_man = 0;
		while (++i < info->n_mans)
		{
			if (flag && isdead(&info->mans[i]))
				flag = 0;
		}
		usleep(10);
	}
	i = -1;
	while (++i < info->n_mans)
		pthread_join(info->mans[i].thread, NULL);
	free_destroy(info);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (argu_check(argc, argv))
		return (print_err("Please use right arguments\n"));
	if (init_arg(&info, argc, argv)
		|| init_man(&info)
		|| init_mutex(&info))
		return (print_err("There is a probelm when you allocate\n"));
	if (go(&info))
		return (1);
	destroy(&info);
	return (0);
}

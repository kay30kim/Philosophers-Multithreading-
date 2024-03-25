/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kay <kay@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 12:58:13 by kay               #+#    #+#             */
/*   Updated: 2024/03/25 15:23:17 by kay              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	done(t_man *philo)
{
	pthread_mutex_lock(&philo->info->finish_mutex);
	philo->info->finish = 1;
	pthread_mutex_unlock(&philo->info->finish_mutex);
}

int	isfinish(t_man *philo)
{
	pthread_mutex_lock(&philo->info->finish_mutex);
	if (philo->info->finish)
	{
		pthread_mutex_unlock(&philo->info->finish_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->info->finish_mutex);
	return (0);
}

long long	get_time(void)
{
	struct timeval	timeval;

	gettimeofday(&timeval, NULL);
	return ((timeval.tv_sec * 1000) + (timeval.tv_usec / 1000));
}

void	print(t_man *philo, char *str)
{
	long long	t;

	pthread_mutex_lock(&philo->info->print_mutex);
	if (!isfinish(philo))
	{
		t = get_time() - philo->info->start_time;
		printf("%lld %d %s\n", t, philo->id, str);
	}
	pthread_mutex_unlock(&philo->info->print_mutex);
	if (str[0] == 'f')
		printf("Philosophers Success\n");
}

void	ft_sleep(t_man *philo, long long ms)
{
	long long	t;

	t = get_time();
	while (!isfinish(philo) && (get_time() - t) < ms)
		usleep(100);
}

int	one_person(t_info *info)
{
	print(&info->mans[0], "has taken a fork");
	ft_sleep(&info->mans[0], info->time_die);
	print(&info->mans[0], "died");
	done(&info->mans[0]);
	return(0);
}

void	eat(t_man *man)
{
	pthread_mutex_lock(&man->info->forks[man->left_fork]);
	print(man, "has taken a fork");
	pthread_mutex_lock(&man->info->forks[man->right_fork]);
	print(man, "has taken a fork");
	print(man, "is eating");
	ft_sleep(man, man->info->time_eat);
	pthread_mutex_lock(&man->info->eat_mutex);
	man->eat_cnt += 1;
	man->last_eat_time = get_time();
	pthread_mutex_unlock(&man->info->eat_mutex);
	pthread_mutex_unlock(&man->info->forks[man->right_fork]);
	pthread_mutex_unlock(&man->info->forks[man->left_fork]);
}

void	*start(void *arg)
{
	t_man	*man;

	man = (t_man *)arg;
	if (man->id % 2 ==0)
		usleep(man->info->time_eat * 1000);
	while (true)
	{
		if (isfinish(man))
			return (0);
		eat(man);
		print(man, "is sleeping");
		ft_sleep(man, man->info->time_sleep);
		print(man, "is thinking");
	}
}

int	create(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->n_mans)
	{
		if (pthread_create(&info->mans[i].thread, NULL, start,
			&(info->mans[i])))
			return (print_err("Error: philos thread create\n"));
	}
	return (0);
}

int	go(t_info *info)
{
	if (info->n_mans == 1)
		return(one_person(info));
	return(create(info));
}
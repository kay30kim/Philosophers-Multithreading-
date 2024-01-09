/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kay <kay@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:46:38 by kay               #+#    #+#             */
/*   Updated: 2024/01/09 12:52:05 by kay              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>

struct s_man;

typedef struct s_info
{
	int				n_mans;
	unsigned long	time_die;
	unsigned long	time_eat;
	unsigned long	time_sleep;
	unsigned long	n_must_eat;
	unsigned long	finish;
	struct s_man	*mans;
	int				*forks;
	pthread_mutex_t *mutexes;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t die_mutex;
}			t_info;

typedef struct s_man
{
	size_t	pos;
	size_t	left_fork;
	size_t	right_fork;
	size_t	nfoods;
	size_t	iseat;
	size_t	last_meal;
	size_t	threshold;
	t_info	*instance;
}			t_man;

int		ft_numcheck(const char *string);
size_t	ft_atol(char* str);
#endif

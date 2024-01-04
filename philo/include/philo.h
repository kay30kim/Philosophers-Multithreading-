/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kay <kay@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:46:38 by kay               #+#    #+#             */
/*   Updated: 2024/01/04 15:07:15 by kay              ###   ########.fr       */
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
	int				amount;
	int				eat;
	int				die;
	int				sleep;
	int				meals;
	int				finish;
	struct s_man	*man;
	int				*forks;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t *forks_mutexes;
	pthread_mutex_t die_mutex;
}t_info;

typedef struct s_man
{
	int		pos;
	int		l_fork;
	int		r_fork;
	int		meals;
	int		eating;
	int		last_meal;
	int		threshold;
	t_info	*instance;
}			t_man;
#endif

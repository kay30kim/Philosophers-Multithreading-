/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kay <kay@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:46:38 by kay               #+#    #+#             */
/*   Updated: 2024/03/25 15:23:49 by kay              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>
# include <unistd.h>
# include <sys/time.h>

struct s_man;

typedef struct s_info
{
	int				n_mans;
	unsigned long	time_die;
	unsigned long	time_eat;
	unsigned long	time_sleep;
	unsigned long	n_must_eat;
	int				n_full_man;
	unsigned long	finish;
	long long		start_time; // change
	struct s_man	*mans;
	pthread_mutex_t	*forks;
	pthread_mutex_t print_mutex; // change
	pthread_mutex_t	eat_mutex; // change
	pthread_mutex_t finish_mutex;   // change
}			t_info;

typedef struct s_man
{
	int					id;
	unsigned long		eat_cnt; // change
	unsigned long		left_fork;
	unsigned long		right_fork;
	unsigned long long	last_eat_time; // change	
	t_info				*info;
	pthread_t			thread;
}			t_man;

int			ft_numcheck(const char *string);
size_t		ft_atol(char* str);
int			go(t_info *info);
size_t		ft_atol(char* str);
int			ft_numcheck(const char *str);
int			argu_check(int argc, char **argv);
int			print_err(char *str);
int			free_man(t_info *info);
int			free_info(t_info *info);
int			free_destroy(t_info *info);
int			isdead(t_man *philo);
void		destroy(t_info *info);
void		done(t_man *philo);
int			isfinish(t_man *philo);
long long	get_time(void);
void		print(t_man *philo, char *str);
void		ft_sleep(t_man *philo, long long ms);
int			one_person(t_info *info);
void		eat(t_man *man);
void		*start(void *arg);
int			create(t_info *info);
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 22:11:27 by anaraujo          #+#    #+#             */
/*   Updated: 2023/02/25 22:17:01 by anaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H


#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
# include <sys/time.h>

typedef struct	s_philo
{
	int	id;
	int	meals_counter;
	int	l_fork;
	int	r_fork;
	int	start_time;
	int	last_ate;
}		t_philo;

typedef struct	s_rules
{
	int					nb_philosophers;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nb_times_must_eat;
	pthread_mutex_t		*forks;
	pthread_mutex_t		meal;
	t_philo				*philos;
}		t_rules;

/******************* Util *********************/
long int	ft_atoi(const char *str);
char		*ft_itoa(int n);

/******************* Time Util *********************/
unsigned long	get_time(void);

/******************* Check_args *********************/
int	ft_check_arg(int argc, char **argv);

/******************* Init *********************/
int	init_all(t_rules *rules, t_philo **philo, char **argv);

int	ft_init_threads(t_rules *rules, t_philo *philo);

/******************* Util *********************/

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 22:11:27 by anaraujo          #+#    #+#             */
/*   Updated: 2023/06/20 20:34:14 by anaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	int				meals_counter;
	int				l_fork;
	int				r_fork;
	unsigned long	last_ate;
	struct s_rules	*rules;
	pthread_t		thread_id;
}		t_philo;

typedef struct s_rules
{
	int					nb_philosophers;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nb_times_must_eat;
	int					nb_total_eat;
	int					stop;
	unsigned long		start_time;
	pthread_mutex_t		*forks;
	pthread_mutex_t		meal;
	pthread_mutex_t		writing;
	pthread_mutex_t		death;
	t_philo				*philos;
}		t_rules;

/******************* Util *********************/
long int		ft_atoi(const char *str);
char			*ft_itoa(int n);

/******************* Time Util *********************/
unsigned long	get_time(void);

/******************* Check_args *********************/
int				ft_check_arg(int argc, char **argv);

/******************* Init *********************/
int				init_all(t_rules *rules, char **argv);

/******************* Threads *********************/
int 			death_check(t_rules	*rules, int n);
int				ft_init_threads(t_rules *rules);

/******************* philo_functions *********************/
void			philo_eat(t_philo *philo, t_rules *rules);
void			ft_sleep(unsigned long duration, t_rules *rules);
void			philo_dead(t_rules *rules, t_philo *philo);
void			philo_print(char *msg, t_philo *philo, int unlock);

#endif
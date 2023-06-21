/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 21:23:18 by anaraujo          #+#    #+#             */
/*   Updated: 2023/06/21 23:15:42 by anaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*This function allow to write the logs in the terminal.
I calcule the timestamp and lock the writing then, I will print the logs.
And after unlock the mutex.*/
void	philo_print(char *msg, t_philo *philo, int unlock)
{
	char	*timestamp;

	(void)unlock;
	timestamp = ft_itoa(get_time() - philo->rules->start_time);
	pthread_mutex_lock(&philo->rules->writing);
	if (death_check(philo->rules) != 1 \
			&& death_check_total_eat(philo->rules) != 1)
		printf("%s %d %s\n", timestamp, philo->id, msg);
	pthread_mutex_unlock(&philo->rules->writing);
	free(timestamp);
}

/*Philosopher will take the left fork and lock and then the right fork and lock.
Then the philosopher will eat and increase the number philo->meals_counter.
After than unlock the forks*/
void	philo_eat(t_philo *philo, t_rules *rules)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&rules->forks[philo->r_fork]);
		philo_print("has taken a fork", philo, 1);
		pthread_mutex_lock(&rules->forks[philo->l_fork]);
		philo_print("has taken a fork", philo, 1);
	}
	else
	{
		pthread_mutex_lock(&rules->forks[philo->l_fork]);
		philo_print("has taken a fork", philo, 1);
		pthread_mutex_lock(&rules->forks[philo->r_fork]);
		philo_print("has taken a fork", philo, 1);
	}
	pthread_mutex_lock(&rules->meal);
	philo_print("is eating", philo, 1);
	philo->last_ate = get_time();
	philo->meals_counter++;
	pthread_mutex_unlock(&rules->meal);
	ft_sleep(rules->time_to_eat, rules);
}

void	philo_eat_unlock_forks(t_philo *philo, t_rules *rules)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&rules->forks[philo->l_fork]);
		pthread_mutex_unlock(&rules->forks[philo->r_fork]);
	}
	else
	{
		pthread_mutex_unlock(&rules->forks[philo->r_fork]);
		pthread_mutex_unlock(&rules->forks[philo->l_fork]);
	}
}

void	philo_eat_one_philo(t_philo *philo, t_rules *rules)
{
	pthread_mutex_lock(&rules->forks[philo->r_fork]);
	philo_print("has taken a fork", philo, 1);
	ft_sleep(rules->time_to_eat, rules);
	pthread_mutex_unlock(&rules->forks[philo->r_fork]);
}

/*This function takes the time in milliseconds and while the time
unless the start time is less than the duration, I call usleep.
After the duration passes, the function will end*/
void	ft_sleep(unsigned long duration, t_rules *rules)
{
	unsigned long	start;

	(void)rules;
	start = 0;
	start = get_time();
	while ((get_time() - start) < duration)
		usleep(duration * 1000);
}

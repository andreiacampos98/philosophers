/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 21:23:18 by anaraujo          #+#    #+#             */
/*   Updated: 2023/03/05 14:32:40 by anaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_bonus.h"

/*This function allow to write the logs in the terminal.
I calcule the timestamp and lock the writing then, I will print the logs.
And after unlock the mutex.*/
void	philo_print(char *msg, t_philo *philo, int unlock)
{
	char	*timestamp;

	timestamp = ft_itoa(get_time() - philo->rules->start_time);
	sem_wait(&philo->rules->writing);
	if (!philo->rules->stop && !philo->rules->nb_times_must_eat)
		printf("%s %d %s\n", timestamp, philo->id, msg);
	if (unlock == 1)
		sem_post(&philo->rules->writing);
	free(timestamp);
}

/*Philosopher will take the left fork and lock and then the right fork and lock.
Then the philosopher will eat and increase the number philo->meals_counter.
After than unlock the forks*/
void	philo_eat(t_philo *philo, t_rules *rules)
{
	sem_wait(&rules->forks[philo->l_fork]);
	philo_print("has taken a fork", philo, 1);
	sem_wait(&rules->forks[philo->r_fork]);
	philo_print("has taken a fork", philo, 1);
	sem_wait(&rules->meal);
	philo_print("is eating", philo, 1);
	philo->last_ate = get_time();
	sem_post(&rules->meal);
	ft_sleep(rules->time_to_eat, rules);
	philo->meals_counter++;
	sem_post(&rules->forks[philo->r_fork]);
	sem_post(&rules->forks[philo->l_fork]);
}

/*This function takes the time in milliseconds and while the time
unless the start time is less than the duration, I call usleep.
After the duration passes, the function will end*/
void	ft_sleep(unsigned long duration, t_rules *rules)
{
	unsigned long	start;

	start = get_time();
	while (rules->stop == 0)
	{
		if ((get_time() - start) >= duration)
			break ;
		usleep(duration * 1000);
	}
}

/*This function will work until the philosophers eat at least
the number of meals that they must eat or until the philosopher 
is starving.
 While i is less than the number of philosophers, I will check 
 the difference between the time at this moment and the last 
 time the philosopher ate. 
If the difference is higher than the time to die. I will print 
the message died. While */
void	philo_dead(t_rules *rules, t_philo *philo)
{
	int	i;

	i = 0;
	while (!rules->nb_total_eat)
	{
		while (i < rules->nb_philosophers)
		{
			sem_wait(&rules->meal);
			if ((int)(get_time() - philo[i].last_ate) >= rules->time_to_die)
			{
				philo_print("died", &philo[i], 0);
				rules->stop = 1;
			}
			sem_post(&rules->meal);
			i++;
		}
		if (rules->stop == 1)
			break ;
		i = 0;
		while (rules->nb_times_must_eat && i < rules->nb_philosophers
			&& philo[i].meals_counter >= rules->nb_times_must_eat)
			i++;
		if (i == rules->nb_philosophers)
			rules->nb_total_eat = 1;
	}
}


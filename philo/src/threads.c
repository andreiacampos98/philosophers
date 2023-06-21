/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:50:21 by anaraujo          #+#    #+#             */
/*   Updated: 2023/06/21 23:11:50 by anaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	death_check_total_eat(t_rules *rules)
{
	int	status;

	status = 0;
	pthread_mutex_lock(&rules->death);
	status = rules->nb_total_eat;
	pthread_mutex_unlock(&rules->death);
	return (status);
}

int	death_check_comp(t_rules *rules, int i)
{
	int	status;

	status = 0;
	pthread_mutex_lock(&rules->death);
	if (rules->philos[i].meals_counter >= rules->nb_eat)
		status = 1;
	pthread_mutex_unlock(&rules->death);
	return (status);
}

/*In this function, I will put the philosophers eating, thinking and sleeping
 until died or achieve the number of times that they must eat.*/
void	*routine(void *arg)
{
	int		i;
	t_philo	*philo;
	t_rules	*rules;

	philo = (t_philo *)arg;
	i = 0;
	rules = philo->rules;
	if (rules->nb_philo == 1)
		philo_eat_one_philo(philo, rules);
	else if (philo->id % 2 == 0 && rules->nb_philo > 1)
		ft_sleep(rules->time_to_eat / 2, rules);
	while (death_check_total_eat(rules) == 0 && rules->nb_philo > 1 \
			&& death_check(rules) == 0)
	{
		philo_eat(philo, rules);
		philo_eat_unlock_forks(philo, rules);
		philo_print("is sleeping", philo, 1);
		ft_sleep(rules->time_to_sleep, rules);
		philo_print("is thinking", philo, 1);
		if (rules->time_to_die - rules->time_to_sleep - rules->time_to_eat > 0)
			ft_sleep((rules->time_to_die - rules->time_to_sleep - \
						rules->time_to_eat) / 2, rules);
	}
	return (NULL);
}

/*This function will close all the threads and mutexs.*/
void	ft_exit_threads(t_rules *rules)
{
	int	i;

	i = 0;
	if (rules->nb_philo == 1)
		pthread_detach(rules->philos[0].thread_id);
	else
	{	
		while (i < rules->nb_philo)
		{
			pthread_join(rules->philos[i].thread_id, NULL);
			i++;
		}
	}
	i = 0;
	while (i < rules->nb_philo)
	{
		pthread_mutex_destroy(&rules->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&rules->meal);
	pthread_mutex_destroy(&rules->writing);
	pthread_mutex_destroy(&rules->death);
	free(rules->philos);
	free(rules->forks);
}

/*For each philosophers, I have one variable pthread_t thread_id, 
that I will initialize.
The pthread_create will call the routine function.
After, I call the function philo_dead and then
I "close" the threads and mutex*/
int	ft_init_threads(t_rules *rules)
{
	int	i;

	i = 0;
	rules->start_time = get_time();
	while (i < rules->nb_philo)
	{
		rules->philos[i].last_ate = get_time();
		if (pthread_create(&rules->philos[i].thread_id, NULL,
				&routine, &(rules)->philos[i]))
		{
			while (i--)
				pthread_join(rules->philos[i].thread_id, NULL);
			return (0);
		}
		i++;
	}
	philo_dead(rules, rules->philos);
	ft_exit_threads(rules);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:50:21 by anaraujo          #+#    #+#             */
/*   Updated: 2023/03/14 23:05:27 by anaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_bonus.h"

/*In this function, I will put the philosophers eating, thinking and sleeping
 until died or achieve the number of times that they must eat.*/
void	*routine(void *arg)
{
	t_philo	*philo;
	t_rules	*rules;

	philo = (t_philo *)arg;
	rules = philo->rules;
	if (philo->id % 2 && rules->nb_philosophers > 1)
	{
		ft_sleep(rules->time_to_eat / 50, rules);
		philo_print("is", philo, 1);
	}
	while (rules->nb_total_eat == 0 && rules->stop == 0)
	{
		philo_eat(philo, rules);
		philo_print("is sleeping", philo, 1);
		ft_sleep(rules->time_to_sleep, rules);
		philo_print("is thinking", philo, 1);
	}
	return (NULL);
}

/*This function will close all the threads and mutexs.*/
void	ft_exit_threads(t_rules *rules)
{
	int	i;

	i = 0;
	if (rules->nb_philosophers == 1)
		pthread_detach(rules->philos[0].thread_id);
	else
	{	
		while (i < rules->nb_philosophers)
		{
			pthread_join(rules->philos[i].thread_id, NULL);
			i++;
		}
	}
	i = 0;
	while (i < rules->nb_philosophers)
	{
		sem_destroy(&rules->forks[i]);
		i++;
	}
	sem_destroy(&rules->meal);
	sem_destroy(&rules->writing);
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
	pthread_t	th;

	i = 0;
	while (i < rules->nb_philosophers)
	{
		rules->(philo)[i].pid = fork();
		if(!rules->(philo)[i].pid)
		{
			routine(&rules->philosophers[i]);
			exit (1);
		}
		i++;
	}
	pthread_create(&th, NULL, wait_children, &(rules)->philos[i]);
	pthread_detach(rules->philos[0].thread_id);
	return (1);
}

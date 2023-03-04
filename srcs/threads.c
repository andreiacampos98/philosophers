/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:50:21 by anaraujo          #+#    #+#             */
/*   Updated: 2023/03/04 19:11:35 by anaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "../includes/philosophers.h"

# define PRINT(name, x) printf("%s: %d\n", name, x);
# define DEBUG

void	*routine(void *arg)
{
	int	i;
	t_philo	*philo;
	t_rules	*rules;

	philo = (t_philo *)arg;
	i = 0;
	rules = philo->rules;
	printf("Thread %d created\n", ((t_philo *)arg)->id);
	while (rules->nb_total_eat == 0 && rules->stop == 0)
	{
		philo_eat(philo, rules);
		philo_print("is sleeping", philo, 1);
		ft_sleep(rules->time_to_sleep, rules);
		philo_print("is thinking", philo, 1);
	}
	return (NULL);
}

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
		pthread_mutex_destroy(&rules->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&rules->meal);
	pthread_mutex_destroy(&rules->writing);
	free(rules->philos);
	free(rules->forks);
}

int	ft_init_threads(t_rules *rules)
{
	int	i;

	i = 0;
	rules->start_time = get_time();
	while (i < rules->nb_philosophers)
	{
		rules->philos[i].last_ate = get_time();
		if (pthread_create(&rules->philos[i].thread_id, NULL,
			&routine, &(rules)->philos[i]))
			return (0);
		i++;
	}
	philo_dead(rules, rules->philos);
	pthread_mutex_unlock(&rules->writing);
	ft_exit_threads(rules);
	return (1);
}

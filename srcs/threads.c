/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:50:21 by anaraujo          #+#    #+#             */
/*   Updated: 2023/03/04 18:10:17 by anaraujo         ###   ########.fr       */
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
	char	*timestamp;

	philo = (t_philo *)arg;
	i = 0;
	rules = philo->rules;
	while (rules->nb_total_eat == 0 && rules->stop == 0)
	{
		philo_eat(philo, rules);
		timestamp = ft_itoa(get_time() - rules->start_time);
		printf("%s philosopher[%i] is sleeping", timestamp, philo->id);
		ft_sleep(rules->time_to_sleep, rules);
		timestamp = ft_itoa(get_time() - rules->start_time);
		printf("%s philosopher[%i] is thinking", timestamp, philo->id);
	}
	printf("Thread %d created\n", ((t_philo *)arg)->id);
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
			printf("A");
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
			&routine, (void *)&(rules)->philos[i]))
			return (0);
		i++;
	}
	philo_dead(rules, rules->philos);
	ft_exit_threads(rules);
	return (1);
}

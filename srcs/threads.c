/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:50:21 by anaraujo          #+#    #+#             */
/*   Updated: 2023/02/25 21:19:50 by anaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "../includes/philosophers.h"

# define PRINT(name, x) printf("%s: %d\n", name, x);
# define DEBUG

void	*routine(void *arg)
{
	// pthread_mutex_t	mutex;
	// t_philo	*a;

	// a = (t_philo *)arg;
	printf("Thread %d created\n", ((t_philo *)arg)->id);
	// free(arg);
	return (NULL);
}

/*	pthread_mutex_lock(&mutex);
	printf("timestamp_in_ms philosopher[%i] has taken a fork", i);
	printf("timestamp_in_ms [%i] is eating", i);
	pthread_mutex_unlock(&mutex);
	printf("timestamp_in_ms philosopher[%i] is sleeping", i);
	printf("timestamp_in_ms philosopher[%i] is thinking", i);
	printf("timestamp_in_ms philosopher[%i] died", i);*/

int	ft_init_threads(t_rules *rules, t_philo *philo)
{
	pthread_t	*th;
	// int	*a;
	int	i;

	i = 0;
	th = malloc(sizeof(pthread_t) * (size_t)rules->nb_philosophers);
	if(th == NULL)
		return (0);
	philo->start_time = get_time();
	while (i < rules->nb_philosophers)
	{
		philo[i].last_ate = get_time();
		if (pthread_create(&th[i], NULL, &routine, (void *)&philo[i]))
			return (0);
		i++;
	}
	i = 0;
	while (i < rules->nb_philosophers)
	{
		if (pthread_join(th[i], NULL))
			return (0);
		i++;
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 21:23:18 by anaraujo          #+#    #+#             */
/*   Updated: 2023/03/04 18:40:49 by anaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/philosophers.h"

void	philo_print(char *msg, t_philo *philo, int unlock)
{
	char	*timestamp;

	timestamp = ft_itoa(get_time() - philo->rules->start_time);
	pthread_mutex_lock(&philo->rules->writing);
	if (!philo->rules->stop && !philo->rules->nb_times_must_eat)
		printf("%s %d %s\n", timestamp, philo->id, msg);
	if (unlock == 1)
		pthread_mutex_unlock(&philo->rules->writing);
	free(timestamp);
}

/*O filosofo vai pegar um garfo e vamos bloquear o mesmo.
Depois printamos a mensagem que "has taken a fork"
Depois o filosofo pega no outro garfo e bloqueamos o mesmo.
Depois bloqueamos o numero de refeicoes e o filosofo come
Aumentamos o contador das refeicoes e damos unlock do mutex*/
void	philo_eat(t_philo *philo, t_rules *rules)
{
	pthread_mutex_lock(&rules->forks[philo->l_fork]);
	philo_print("has taken a fork", philo, 1);
	pthread_mutex_lock(&rules->forks[philo->r_fork]);
	philo_print("has taken a fork", philo, 1);
	pthread_mutex_lock(&rules->meal);
	philo_print("is eating", philo, 1);
	philo->last_ate = get_time();
	pthread_mutex_unlock(&rules->meal);
	ft_sleep(rules->time_to_eat, rules);
	philo->meals_counter++;
	pthread_mutex_unlock(&rules->forks[philo->r_fork]);
	pthread_mutex_unlock(&rules->forks[philo->l_fork]);
}

void	ft_sleep(unsigned long duration, t_rules *rules)
{
	unsigned long	start;

	start = get_time();
	while(rules->stop == 0)
	{
		if((get_time() - start) >= duration)
			break ;
		usleep(duration * 1000);
	}
}

/*Enquanto n*/
void	philo_dead(t_rules *rules, t_philo *philo)
{
	int	i;

	i = 0;
	while (!rules->nb_total_eat)
	{
		while (i < rules->nb_philosophers)
		{
			pthread_mutex_lock(&rules->meal);
			if ((int)(get_time() - philo[i].last_ate) >= rules->time_to_die)
			{
				philo_print("died", &philo[i], 0);	
				rules->stop = 1;
			}
			pthread_mutex_unlock(&rules->meal);
			i++;
		}
		if (rules->stop == 1)
			break;
		i = 0;
		while (rules->nb_times_must_eat && i < rules->nb_philosophers
				&& philo[i].meals_counter >= rules->nb_times_must_eat)
			i++;
		if (i == rules->nb_philosophers)
			rules->nb_total_eat = 1;
	}
}
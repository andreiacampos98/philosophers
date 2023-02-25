/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 21:23:18 by anaraujo          #+#    #+#             */
/*   Updated: 2023/02/25 22:18:22 by anaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/philosophers.h"

/*O filosofo vai pegar um garfo e bvamos bloquear o mesmo.
Depois printamos a mensagem que "has taken a fork"
Depois o filosofo pega no outro garfo e bloqueamos o mesmo.
Depois bloqueamos o numero de refeicoes e o filosofo come
Aumentamos o contador das refeicoes e damos unlock do mutex*/
void	philo_eat(t_philo *philo, t_rules *rules)
{
	char	*timestamp;

	pthread_mutex_lock(&rules->forks[philo->l_fork]);
	timestamp = ft_itoa(get_time() - philo->start_time);
	printf("%s philosopher[%i] has taken a fork", timestamp, philo->id);
	pthread_mutex_lock(&rules->forks[philo->r_fork]);
	timestamp = ft_itoa(get_time() - philo->start_time);
	printf("%s philosopher[%i] has taken a fork", timestamp, philo->id);
	pthread_mutex_lock(&rules->meal);
	timestamp = ft_itoa(get_time() - philo->start_time);
	printf("%s philosopher[%i] is eating", timestamp, philo->id);
	philo->last_ate = get_time();
	pthread_mutex_unlock(&rules->meal);
	//new_sleep(); //colocar a dormir again
	philo->meals_counter++;
	pthread_mutex_unlock(&rules->forks[philo->r_fork]);
	pthread_mutex_unlock(&rules->forks[philo->l_fork]);
	free(timestamp);
}

/*Enquanto n*/
/*void	philo_dead(t_rules *rules, t_philo *philo)
{
	printf("%s philosopher[%i] is thinking", philo->id);
	printf("%s philosopher[%i] died", philo->id);
	printf("%s philosopher[%i] is sleeping", philo->id);
	
}*/

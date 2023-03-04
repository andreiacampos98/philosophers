/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:48:02 by anaraujo          #+#    #+#             */
/*   Updated: 2023/03/04 19:22:59 by anaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/philosophers.h"

void	initialize_rules(t_rules *rules, char **argv)
{
	rules->nb_philosophers = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	rules->start_time = 0;
	rules->nb_total_eat = 0;
	rules->stop = 0;
	if (argv[5])
		rules->nb_times_must_eat = ft_atoi(argv[5]);
	else
		rules->nb_times_must_eat = 0;
}

int	initialize_philo(t_philo **philo, t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->nb_philosophers)
	{
		(*philo)[i].id = i + 1;
		(*philo)[i].meals_counter = 0;
		(*philo)[i].l_fork = i;
		(*philo)[i].rules = rules;
		if (i - 1 < 0)
			(*philo)[i].r_fork = rules->nb_philosophers - 1;
		else
			(*philo)[i].r_fork = i - 1;
		i++;
	}
	return (1);
}

int	ft_init_mutex(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->nb_philosophers)
	{
		if(pthread_mutex_init(&(rules->forks[i]), NULL))
			return(0);
		i++;
	}
	if (pthread_mutex_init(&rules->meal, NULL))
			return(0);
	if (pthread_mutex_init(&rules->writing, NULL))
			return(0);
	return (1);
}

int	init_all(t_rules *rules, char **argv)
{
	initialize_rules(rules, argv);
	rules->philos = (t_philo *)malloc(sizeof(t_philo) * rules->nb_philosophers);
	if (!(rules->philos))
		return (0);
	rules->forks = malloc(sizeof(pthread_mutex_t) * rules->nb_philosophers);
	if (!rules->forks)
	{
		free(rules->philos);
		return (0);
	}
	if (ft_init_mutex(rules) == 0)
	{
		free(rules->philos);
		free(rules->forks);
		return (0);
	}
	if (initialize_philo(&(rules)->philos ,rules) == 0)
	{
		free(rules->philos);
		free(rules->forks);
		return (0);
	}
	return (1);
}

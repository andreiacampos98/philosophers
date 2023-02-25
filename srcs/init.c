/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:48:02 by anaraujo          #+#    #+#             */
/*   Updated: 2023/02/25 20:20:53 by anaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/philosophers.h"

int	initialize_rules(t_rules *rules, char **argv)
{
	rules->nb_philosophers = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	/*if (rules->nb_philosophers < 2 || rules->time_to_die < 0
		|| rules->time_to_eat < 0 || rules->time_to_sleep < 0)
		return (0);*/
	if (argv[5])
	{
		rules->nb_times_must_eat = ft_atoi(argv[5]);
		if (rules->nb_times_must_eat <= 0)
			return (0);
	}
	else
		rules->nb_times_must_eat = -1;
	return (1);
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
		if (i - 1 < 0)
			(*philo)[i].r_fork = rules->nb_philosophers - 1;
		else
			(*philo)[i].r_fork = i - 1;
		i++;
	}
	return (1);
}

int	init_all(t_rules *rules, t_philo **philo, char **argv)
{
	if (initialize_rules(rules, argv) == 0)
	{
		printf("Here\n");
		return(0);
	}
	*philo = (t_philo *)malloc(sizeof(t_philo) * rules->nb_philosophers);
	if (!(*philo))
	{
		printf("Here 2\n");
		return (0);
	}
	if (initialize_philo(philo, rules) == 0)
	{
		printf("Here 3\n");
		return (0);
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:48:02 by anaraujo          #+#    #+#             */
/*   Updated: 2023/03/05 18:39:10 by anaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_bonus.h"

/*The function initialize the structure rules which contains:
	the number of philosophers;
	time to die;
	time to eat;
	time to sleep;
	start time, when starts the program;
	nb_total_eat which is a bolean that will be 1 if all philosophers
		eat at least the number of times they must eat (argument 5)
	nb_times_must_eat is the number of times the philosophers must eat 
		and then the program finish. The program can finish earlier 
		if one of the philosophers died.*/
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

/*In the structure rules, I create three variables sem:
	forks
	meal
	writing
Now it is necessary initialize the variables with the function
sem_open, but before I will call sem_unlink to have sure 
if the semaphore is open, it will be close.
The semaphore is destroyed once all other processes that have 
the semaphore open close it.
The function sem_open() creates a new POSIX semaphore or opens
an existing semaphore.
S_IRWXU this is equivalent to ‘(S_IRUSR | S_IWUSR | S_IXUSR)’.
S_IRUSR Permits the creator of the named semaphore to open the 
semaphore in read mode.
S_IWUSR Permits the creator of the named semaphore to open the 
semaphore in write mode
S_IXUSR Execute (for ordinary files) or search (for directories) 
permission bit for the owner of the file*/
int	ft_init_sem(t_rules *rules)
{
	sem_unlink("/philo_forks");
	sem_unlink("/philo_writing");
	sem_unlink("/philo_meal");
	rules->forks = sem_open("/philo_forks", O_CREAT, S_IRWXU, rules->nb_philosophers);
	rules->writing = sem_open("/philo_writing", O_CREAT, S_IRWXU, 1);
	rules->meal = sem_open("/philo_meal", O_CREAT, S_IRWXU, 1);
	if (rules->forks <= 0 || rules->writing <= 0 || rules->meal <= 0)
		return (0);
	return (1);
}

/*The function initialize the structure philo which contain:
	the id of the philosopher;
	meals_counter which says how many meals the philosopher eat;
	l_fork, the number of left fork 
	r_fork, the number of right fork;
	last_ate, what time the philosopher eat for the last time*/
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

/*This funtion initialize all the variables*/
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
	if (ft_init_sem(rules) == 0)
	{
		free(rules->philos);
		free(rules->forks);
		return (0);
	}
	if (initialize_philo(&(rules)->philos, rules) == 0)
	{
		free(rules->philos);
		free(rules->forks);
		return (0);
	}
	return (1);
}

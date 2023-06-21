/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 22:15:10 by anaraujo          #+#    #+#             */
/*   Updated: 2023/06/21 23:30:32 by anaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*This function will work until the philosophers eat at least
the number of meals that they must eat or until the philosopher 
is starving.
 While i is less than the number of philosophers, I will check 
 the difference between the time at this moment and the last 
 time the philosopher ate. 
If the difference is higher than the time to die. I will print 
the message died. While */
void	philo_dead_aux(t_rules *r, int i)
{
	if (i == r->nb_philo)
	{
		pthread_mutex_lock(&r->death);
		r->nb_total_eat = 1;
		pthread_mutex_unlock(&r->death);
	}
}

void	philo_dead(t_rules *r, t_philo *philo)
{
	int	i;

	i = 0;
	while (r->nb_total_eat == 0)
	{
		while (i < r->nb_philo && death_check(r) == 0)
		{
			pthread_mutex_lock(&r->meal);
			if ((int)(get_time() - philo[i].last_ate) >= r->time_to_die)
			{
				philo_print("died", &philo[i], 0);
				r->stop = 1;
			}
			pthread_mutex_unlock(&r->meal);
			i++;
		}
		if (death_check(r) == 1)
			break ;
		i = 0;
		while (r->nb_eat != 0 && i < r->nb_philo && death_check_comp(r, i) == 1)
			i++;
		philo_dead_aux(r, i);
	}
}

/*Initially, I verify the arguments.
Then I will initialize the two structures
Then I will start the threads.*/
int	main(int argc, char **argv)
{
	t_rules	rules;

	if (ft_check_arg(argc, argv) == 0)
		return (0);
	if (init_all(&rules, argv) == 0)
	{
		return (0);
	}
	if (ft_init_threads(&rules) == 0)
		return (0);
	return (1);
}

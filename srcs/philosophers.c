/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 22:15:10 by anaraujo          #+#    #+#             */
/*   Updated: 2023/02/25 21:13:37 by anaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/philosophers.h"

int	main(int argc, char **argv)
{
	t_rules	rules;
	t_philo	*philo;

	philo = NULL;
	if (ft_check_arg(argc, argv) == 0)
		return(0);
	if (init_all(&rules, &philo, argv) == 0)
	{
		printf("w");
		return(0);
	}
	if(ft_init_threads(&rules, philo) == 0)
		return (0);
	return(1);
}

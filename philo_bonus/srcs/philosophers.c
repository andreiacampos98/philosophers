/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 22:15:10 by anaraujo          #+#    #+#             */
/*   Updated: 2023/03/05 14:14:25 by anaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_bonus.h"
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
	
	return (1);
}

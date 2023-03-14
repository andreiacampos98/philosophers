/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:20:13 by anaraujo          #+#    #+#             */
/*   Updated: 2023/03/14 21:29:19 by anaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
/*The function check if the character is a number.*/
int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

/*The function check if the character is a signal.*/
int	ft_issign(char c)
{
	return (c == '+' || c == '-');
}

/*The function check if the argument is a number.*/
static int	arg_is_number(char *av)
{
	int	i;

	i = 0;
	if (ft_issign(av[i]) && av[i + 1] != '\0')
		i++;
	while (av[i] && ft_isdigit(av[i]))
		i++;
	if (av[i] != '\0' && !ft_isdigit(av[i]))
		return (0);
	return (1);
}

/*The function check if the arguments are 4 or five*/
int	ft_check_nb_args(int argc, char **argv)
{
	if (argc < 5)
	{
		printf("The number of arguments are less than expected");
		return (0);
	}
	if (argc > 6)
	{
		printf("The number of arguments are more than expected");
		return (0);
	}
	if (ft_atoi(argv[1]) == 0)
	{
		printf("The number of philosophers should be higher than 0");
		return (0);
	}
	return (1);
}

/*The fucntion check for each argument if the argument is a number 
and if the argument is a positive INT.*/
int	ft_check_arg(int argc, char **argv)
{
	if (ft_check_nb_args(argc, argv) == 0)
	{
		return (0);
	}
	while (argc > 1)
	{
		if (arg_is_number(argv[argc - 1]) == 0)
		{
			printf("The argument is not a number.");
			return (0);
		}
		if (ft_atoi(argv[argc - 1]) > INT_MAX || ft_atoi(argv[argc - 1]) <= 0)
		{
			printf("The argument is not a positive INT");
			return (0);
		}
		argc--;
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 13:00:35 by anaraujo          #+#    #+#             */
/*   Updated: 2023/06/21 23:01:17 by anaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long int	ft_atoi(const char *str)
{
	int			i;
	long int	res;
	int			s;

	i = 0;
	res = 0;
	s = 1;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			s *= -1;
		i++;
	}
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		res = (str[i] - '0') + (res * 10);
		i++;
	}
	return (res * s);
}

static int	ft_count_digits(unsigned int nb, int dig)
{
	unsigned int	aux;

	aux = nb;
	dig++;
	while (aux / 10 > 0)
	{
		dig++;
		aux /= 10;
	}
	return (dig);
}

static char	*ft_fill_str(int n, char *str, int dig, unsigned int nb)
{
	int	i;

	i = dig - 1;
	while (i >= 0)
	{
		if (n < 0 && i == 0)
			str[i] = '-';
		else
		{
			str[i] = nb % 10 + '0';
			nb /= 10;
		}
		i--;
	}
	str[dig] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	unsigned int	nb;
	int				dig;
	char			*str;

	nb = n;
	dig = 0;
	if (nb == 0)
	{
		str = (char *)malloc(sizeof(char) * 1 + 1);
		if (str == NULL)
			return (0);
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	if (n < 0)
	{
		dig++;
		nb *= -1;
	}
	dig = ft_count_digits(nb, dig);
	str = (char *)malloc((dig) * sizeof(char) + 1);
	if (str == NULL)
		return (0);
	return (ft_fill_str(n, str, dig, nb));
}

/*A microsecond is a unit of time. 
There are 1,000,000 microseconds in a second. 
The next function returns miliseconds.*/
unsigned long	get_time(void)
{
	struct timeval	x;

	gettimeofday(&x, NULL);
	return ((x.tv_sec * 1000) + (x.tv_usec / 1000));
}

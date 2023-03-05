/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 22:05:13 by anaraujo          #+#    #+#             */
/*   Updated: 2023/03/05 13:37:46 by anaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/*A microsecond is a unit of time. 
There are 1,000,000 microseconds in a second. 
The next function returns miliseconds.*/
unsigned long	get_time(void)
{
	struct timeval	x;

	gettimeofday(&x, NULL);
	return ((x.tv_sec * 1000) + (x.tv_usec / 1000));
}

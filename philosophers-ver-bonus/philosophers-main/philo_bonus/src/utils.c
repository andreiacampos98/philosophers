/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 12:24:16 by raccoman          #+#    #+#             */
/*   Updated: 2023/03/14 22:51:50 by anaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atol(const char *string, size_t *dst)
{
	int	i;

	i = 0;
	if (string[i] == '\0')
		return (1);
	*dst = 0;
	while (string[i] && string[i] >= '0' && string[i] <= '9')
	{
		*dst = *dst * 10 + (string[i] - '0');
		i++;
	}
	if (string[i] != '\0')
		return (1);
	return (0);
}

size_t	get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(size_t ms)
{
	size_t	end;

	end = get_time() + ms;
	while (get_time() < end)
		usleep(ms / 1000);
}

/*The waitpid() system call suspends execution of the current 
process until a child specified by pid argument has changed state. 
By default, waitpid() waits only for terminated children, 
but this behaviour is modifiable via the options argument, as described below.
0 meaning wait for any child process whose process group ID is equal to that of the calling process. */
void	*wait_children(void *vinstance)
{
	size_t	i;
	t_main	*instance;

	i = -1;
	instance = (t_main *)vinstance;
	while (++i < instance->amount)
		waitpid(instance->philosophers[i].pid, NULL, 0);
	exit(0);
}

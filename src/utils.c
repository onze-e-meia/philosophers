/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 13:42:25 by tforster          #+#    #+#             */
/*   Updated: 2024/07/05 15:31:10 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// void	get_time(t_tval time)
// {
// 	gettimeofday(&time, NULL);
// }

t_usec	get_time()
{
	struct timeval	time;
	struct timeval	tv2;

	gettimeofday(&time, NULL);
	// usleep(400 * 1000);
	// gettimeofday(&tv2, NULL);

	// printf(">>> TIME [%ld] [%ld]\n", time.tv_sec, time.tv_usec);
	// printf(">>> TIME [%ld] [%ld]\n", tv2.tv_sec, tv2.tv_usec);
	return (time.tv_sec * 1000000 + time.tv_usec);
}

void	put_str(int fd, char *str)
{
	while (*str)
		write(fd, str++, 1);
}

int	is_digit(int ch)
{
	return ('0' <= ch && ch <= '9');
}

int	atoi(const char *nbr)
{
	int	sign;
	int	rslt;

	while (*nbr == ' ' || (*nbr >= 9 && *nbr <= 13))
		nbr++;
	sign = 1;
	if (*nbr == '-')
	{
		sign *= -1;
		nbr++;
	}
	else if (*nbr == '+')
		nbr++;
	rslt = 0;
	while (*nbr)
	{
		rslt = rslt * 10 + (*nbr - '0');
		nbr++;
	}
	return (sign * rslt);
}

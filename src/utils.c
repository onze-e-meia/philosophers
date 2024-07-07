/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 13:42:25 by tforster          #+#    #+#             */
/*   Updated: 2024/07/07 15:32:24 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_usec	usec_time(void)
{
	t_tval	tval;

	gettimeofday(&tval, NULL);
	return (tval.tv_sec * 1000000 + tval.tv_usec);
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

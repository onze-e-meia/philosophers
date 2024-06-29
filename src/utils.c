/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 13:42:25 by tforster          #+#    #+#             */
/*   Updated: 2024/06/29 18:44:10 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	put_str(int fd, char *str)
{
	while (*str)
		write(fd, str++, 1);
}

int	arg_error(char i, t_arg_error err)
{
	const char	*error_msg[5] = {ERR01, ERR02, ERR03, ERR04, ERR05};

	write(2, "[", 1);
	write(2, &i, 1);
	write(2, "] :", 2);
	if (i == '5' && err == TOO_BIG)
		put_str(2, (char *) error_msg[4]);
	else
		put_str(2, (char *) error_msg[err - 1]);
	return (err);
}

int	is_digit(int ch)
{
	return ('0' <= ch && ch <= '9');
}

int	str_is_digit(char i, char *nbr)
{
	int	len;

	len = 0;
	while (*nbr)
	{
		if (is_digit(*nbr))
			nbr++;
		else
			return (arg_error(i, NOT_DIGIT));
		if (len++ > 8)
			return (arg_error(i, TOO_BIG));
	}
	return (0);
}

int	check_argv(char i, char *nbr)
{
	int	sign;
	int	err;

	if (!*nbr)
		return (arg_error(i, EMPTY_ARG));
	sign = 1;
	if (*nbr == '-')
	{
		nbr++;
		sign = -1;
	}
	else if (*nbr == '+')
		nbr++;
	if (*nbr == '\0')
		return (arg_error(i, NOT_DIGIT));
	err = str_is_digit(i, nbr);
	if (!err)
		if (sign == -1)
			return (arg_error(i, NEG_ARG));
	return (err);
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

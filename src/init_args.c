/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:52:31 by tforster          #+#    #+#             */
/*   Updated: 2024/07/04 14:52:36 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_argv(char i, char *nbr);
int	arg_error(char i, t_arg_error err);
int	str_is_digit(char i, char *nbr);

int	init_args(int argc, char **argv, t_args *args)
{
	int	i;
	int	err;

	i = 1;
	err = 0;
	while (i < argc)
	{
		if (check_argv(i + '0', argv[i]))
			err++;
		i++;
	}
	if (err)
		return (err);
	args->nb_philos = atoi(argv[1]);
	args->live = atoi(argv[2]) * 1000;
	args->eat = atoi(argv[3]) * 1000;
	args->sleep = atoi(argv[4]) * 1000;
	args->times = -1;
	args->dead = false;
	if (argc == 6)
		args->times = atoi(argv[5]);
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

int	arg_error(char i, t_arg_error err)
{
	const char	*error_msg[5] = {ERR01, ERR02, ERR03, ERR04, ERR05};

	write(2, "[", 1);
	write(2, &i, 1);
	write(2, "] :", 2);
	if (i == '5' && err == TOO_BIG)
		put_str(STDERR_FILENO, (char *) error_msg[4]);
	else
		put_str(STDERR_FILENO, (char *) error_msg[err - 1]);
	return (err);
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

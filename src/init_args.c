/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:52:31 by tforster          #+#    #+#             */
/*   Updated: 2024/07/07 20:57:16 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	time_len(t_args *args);
static int	check_argv(char i, char *nbr);
static int	arg_error(char i, t_arg_error err);
static int	str_is_digit(char i, char *nbr);

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
	args->nb_phi = atoi(argv[1]);
	args->fed_phi = 0;
	args->t_live = atoi(argv[2]) * 1000;
	args->t_eat = atoi(argv[3]) * 1000;
	args->t_sleep = atoi(argv[4]) * 1000;
	args->nb_meals = -1;
	args->dead = false;
	if (argc == 6)
		args->nb_meals = atoi(argv[5]);
	return (time_len(args));
}

static int	time_len(t_args *args)
{
	int	err;

	err = 0;
	if (args->nb_phi == 0)
		err = (arg_error('1', TOO_SMAL));
	if (args->t_live < 60000)
		err = (arg_error('2', TOO_SMAL));
	if (args->t_eat < 60000)
		err = (arg_error('3', TOO_SMAL));
	if (args->t_sleep < 60000)
		err = (arg_error('4', TOO_SMAL));
	if (args->nb_meals == 0)
		err = (arg_error('5', TOO_SMAL));
	return (err);
}

static int	check_argv(char i, char *nbr)
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
	while (*nbr == '0')
		nbr++;
	if (*nbr == '\0')
		return (arg_error(i, NOT_DIGIT));
	err = str_is_digit(i, nbr);
	if (!err)
		if (sign == -1)
			return (arg_error(i, NEG_ARG));
	return (err);
}

static int	arg_error(char i, t_arg_error err)
{
	const char	*error_msg[7] = {ERR0, ERR1, ERR2, ERR3, ERR4, ERR5, ERR6};

	write(2, "[", 1);
	write(2, &i, 1);
	write(2, "] :", 2);
	if ((i == '1' || i == '5') && err == TOO_SMAL)
		put_str(STDERR_FILENO, (char *) error_msg[4]);
	else if ((i == '2' || i == '3' || i == '4') && err == TOO_SMAL)
		put_str(STDERR_FILENO, (char *) error_msg[5]);
	else if ((i == '2' || i == '3' || i == '4') && err == TOO_BIG)
		put_str(STDERR_FILENO, (char *) error_msg[3]);
	else if (i == '5' && err == TOO_BIG)
		put_str(STDERR_FILENO, (char *) error_msg[6]);
	else
		put_str(STDERR_FILENO, (char *) error_msg[err -1]);
	return (err);
}

static int	str_is_digit(char i, char *nbr)
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

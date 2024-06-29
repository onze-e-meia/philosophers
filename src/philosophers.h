/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:36:34 by tforster          #+#    #+#             */
/*   Updated: 2024/06/29 17:48:04 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

# define ERR01 "Argument is empty.\n"
# define ERR02 "Argument is a negative number.\n"
# define ERR03 "Argument is not a number.\n"
# define ERR04 "Argument time (micro_s) is bigger then 16 minutes.\n"
# define ERR05 "Argument times to eat is bigger then 999999999.\n"

typedef enum e_arg_error
{
	ARG_OK = 0,
	EMPTY_ARG,
	NEG_ARG,
	NOT_DIGIT,
	TOO_BIG,
}	t_arg_error;

typedef struct s_args
{
	int	nb_philos;
	int	live;
	int	eat;
	int	sleep;
	int	times;
}		t_args;

int	check_argv(char i, char *nbr);
int	atoi(const char *str);

#endif

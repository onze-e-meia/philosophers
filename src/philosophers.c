/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:28:26 by tforster          #+#    #+#             */
/*   Updated: 2024/06/29 18:46:59 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
	args->live = atoi(argv[2]);
	args->eat = atoi(argv[3]);
	args->sleep = atoi(argv[4]);
	args->times = -1;
	if (argc == 6)
		args->times = atoi(argv[5]);
	return (0);
}

int	main(int argc, char **argv)
{
	t_args	args;
	int		flag;

	if (argc < 5)
		return (printf("To few arguments, need 4 or 5 (int)!\n"));
	else if (argc > 6)
		return (printf("To many arguments, need 4 or 5 (int)!\n"));
	flag = init_args(argc, argv, &args);
	if (!flag)
	{
		printf("1 %d\n", args.nb_philos);
		printf("2 %d\n", args.live);
		printf("3 %d\n", args.eat);
		printf("4 %d\n", args.sleep);
		printf("5 %d\n", args.times);
	}
	return (flag);
}

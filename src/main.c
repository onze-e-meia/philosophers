/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:28:26 by tforster          #+#    #+#             */
/*   Updated: 2024/07/07 20:31:18 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_args		args;
	t_locks		*locks;
	t_phi		*phi;
	t_thread	*thread;
	int			flag;

	if (argc < 5)
		return (printf("To few arguments, need 4 or 5 (int)!\n"));
	else if (argc > 6)
		return (printf("To many arguments, need 4 or 5 (int)!\n"));
	flag = init_args(argc, argv, &args);
	if (flag)
		return (flag);
	locks = init_mutex(args.nb_phi);
	phi = init_phi(&args, locks);
	thread = init_threads(&args, phi);
	grim_reaper(&args, locks, phi);
	join_threads(thread, phi, args.nb_phi);
	destroy_mutex(locks, args.nb_phi);
	return (flag);
}

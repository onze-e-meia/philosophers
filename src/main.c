/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:28:26 by tforster          #+#    #+#             */
/*   Updated: 2024/07/06 22:01:58 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// void	*starve(void *args)
// {
// 	t_args	*philos;

// 	philos = (t_args *) args;
// 	// struct timeval	tv1;
// 	// struct timeval	tv2;

// 	printf("%ld %s\n", philos->epoch, "ERROR");



// 	pthread_mutex_lock(&philos->write);

// 	int	p_nth = *philos->ctrl;
// 	printf(">>>CTRL [%d]\n", *philos->ctrl);
// 	int	total = philos->nb_phi;
// 	pthread_mutex_unlock(&philos->write);

// 	// pthread_mutex_lock(&philos->forks[p_nth % total]);
// 	// pthread_mutex_lock(&philos->forks[(p_nth + 1) % total]);

// 	printf("[%d] PICK fork [%d]\n", p_nth, p_nth % total);
// 	printf("[%d] PICK fork [%d]\n", p_nth, (p_nth + 1) % total);

// 	// pthread_mutex_unlock(&philos->forks[(p_nth + 1) % total]);
// 	// pthread_mutex_unlock(&philos->forks[p_nth % total]);

// 	// long seconds = tv2.tv_sec - tv1.tv_sec;
// 	// long microseconds = tv2.tv_usec - tv1.tv_usec;
// 	// if (microseconds < 0) {
// 	// 	seconds -= 1;
// 	// 	microseconds += 1000000;
// 	// }
//     // printf("Elapsed time: %ld seconds and %ld microseconds\n", seconds, microseconds);
// 	// printf("TIME! [%ld] [%ld]\n", tv1.tv_sec, tv1.tv_usec);
// 	// printf("AFTER! [%ld] [%ld]\n", tv2.tv_sec, tv2.tv_usec);
// 	// printf("[%ld] [%ld] [%ld] [%ld]\n",
// 	// 	tv2.tv_sec - tv1.tv_sec,
// 	// 	tv2.tv_usec - tv1.tv_usec,
// 	// 	(tv2.tv_sec - tv1.tv_sec) * 1000 + (tv2.tv_usec - tv1.tv_usec) / 1000,
// 	// 	(tv2.tv_sec - tv1.tv_sec) * 1000000 + (tv2.tv_usec - tv1.tv_usec));
// 	return (NULL);
// }

int	main(int argc, char **argv)
{
	t_args		args;
	t_locks		*locks;
	t_phi		*phi;
	t_thread	*thread;

	int		index;

	if (argc < 5)
		return (printf("To few arguments, need 4 or 5 (int)!\n"));
	else if (argc > 6)
		return (printf("To many arguments, need 4 or 5 (int)!\n"));

	int		flag;
	flag = init_args(argc, argv, &args);
	if (flag)
		return (flag);
	else
	{
		printf("1 %d\n", args.nb_phi);
		printf("2 %ld\n", args.t_live);
		printf("3 %ld\n", args.t_eat);
		printf("4 %ld\n", args.t_sleep);
		printf("5 %d\n", args.nb_meals);
	}

	locks = init_mutex(args.nb_phi);
	phi = init_phi(&args, locks);
	thread = init_threads(&args, phi);

	grim_reaper(&args, locks, phi);

	join_threads(thread, phi, args.nb_phi);

	destroy_mutex(locks, args.nb_phi);
	return (flag);
}

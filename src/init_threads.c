/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:49:10 by tforster          #+#    #+#             */
/*   Updated: 2024/07/05 15:05:59 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_phi	*init_philo(t_args *args, t_locks *locks, int index)
{
	int		total;
	t_phi	*phi;

	total = args->nb_philos;
	phi = malloc(sizeof(t_phi));
	if (!phi)
		return (NULL);
	phi->id = index + 1;
	gettimeofday(&phi->t0, NULL);
	phi->eat = 0;
	phi->args = args;
	if (phi->id % 2 != 0)
	{
		phi->l_fork = &locks->forks[index % total];
		phi->r_fork = &locks->forks[(index + 1) % total];
	}
	else
	{
		phi->l_fork = &locks->forks[(index + 1) % total];
		phi->r_fork = &locks->forks[index % total];
	}
	phi->write = &locks->write;
	phi->dead = &locks->dead;
	return (phi);
}

// t_phi	*init_threads(t_args *args, t_locks *locks)
pthread_t	*init_threads(t_args *args, t_locks *locks)
{
	int		total;
	int		index;
	t_phi	*phi;
	pthread_t	*thread;

	total = args->nb_philos;
	// phi = malloc(args->nb_philos * sizeof(t_phi));
	thread = malloc(total * sizeof(pthread_t));
	// index = 0;
	// while (index < total)
	// {
	// 	phi[index].id = 1 + index;
	// 	phi[index].born = get_time();
	// 	phi[index].args = args;
	// 	phi[index].l_fork = locks->forks[index % total];
	// 	phi[index].r_fork = locks->forks[(index + 1) % total];
	// 	index++;
	// }

	index = 0;
	while (index < total)
	{
		// args->ctrl = malloc(sizeof(int));
		// args->ctrl = &index;
		// printf("CTRL [%d]\n", *args->ctrl);
		// if (pthread_create(&phi[index].thread, NULL, starve, (void *) init_philo(args, locks, index)))
		// 	return (NULL);
		if (pthread_create(&thread[index], NULL, greedy_phi, (void *) init_philo(args, locks, index)))
			return (NULL);
		index++;
	}
	// return (phi);
	return (thread);
}

// int	join_threads(t_args *args, pthread_t *philos)
// int	join_threads(t_phi *phi, int nb_philos)
int	join_threads(pthread_t *thread, int nb_philos)
{
	int	index;

	index = 0;
	while (index < nb_philos)
	{
		// if (pthread_join(phi[index++].thread, NULL))
		if (pthread_join(thread[index++], NULL))
			return (1);
	}
	return (0);
}

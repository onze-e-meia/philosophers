/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:49:10 by tforster          #+#    #+#             */
/*   Updated: 2024/07/06 20:36:05 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_phi	*init_phi(t_args *args, t_locks *locks)
{
	int		index;
	t_phi	*phi;

	phi = malloc(args->nb_phi * sizeof(t_phi));
	if (!phi)
		return (NULL);
	index = 0;
	while (index < args->nb_phi)
	{
		phi[index].id = index + 1;
		phi[index].eaten = 0;
		phi[index].args = args;
		if (phi->id % 2 != 0)
		{
			phi[index].l_fork = &locks->forks[index % args->nb_phi];
			phi[index].r_fork = &locks->forks[(index + 1) % args->nb_phi];
		}
		else
		{
			phi[index].l_fork = &locks->forks[(index + 1) % args->nb_phi];
			phi[index].r_fork = &locks->forks[index % args->nb_phi];
		}
		phi[index].write = &locks->write;
		phi[index].meal = &locks->meal;
		phi[index].dead = &locks->dead;
		index++;
	}
	return (phi);
}

t_phi	*init_dining(t_phi *phi)
{
	t_tval tval;

	gettimeofday(&tval, NULL);
	phi->time = (tval.tv_sec * 1000000 + tval.tv_usec);
	return(phi);
}

t_thread	*init_threads(t_args *args, t_phi *phi)
{
	int			index;
	t_tval		tval;
	t_thread	*thread;

	thread = malloc(args->nb_phi * sizeof(t_thread));
	if (!thread)
		return (NULL);
	index = 0;
	gettimeofday(&tval, NULL);
	args->t0 = (tval.tv_sec * 1000000 + tval.tv_usec);
	while (index < args->nb_phi)
	{
		if (pthread_create(&thread[index], NULL, routine, (void *) init_dining(&phi[index])))
			return (NULL);
		index++;
	}
	return (thread);
}

int	join_threads(t_thread *thread, t_phi *phi, int nb_phi)
{
	int	index;

	index = 0;
	while (index < nb_phi)
	{
		if (pthread_join(thread[index++], NULL))
			return (1);
	}
	free(thread);
	free(phi);
	return (0);
}

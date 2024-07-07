/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:31:20 by tforster          #+#    #+#             */
/*   Updated: 2024/07/07 14:54:23 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// int	init_mutex(t_locks *locks, int nb_phi)
t_locks	*init_mutex(int nb_phi)
{
	int		index;
	t_locks	*locks;

	locks = malloc(sizeof(t_locks));
	if (!locks)
		return (NULL);
	locks->forks = malloc(nb_phi * sizeof(pthread_mutex_t));
	if (!locks->forks)
		return (NULL);
	index = 0;
	while (index < nb_phi)
		if (pthread_mutex_init(&locks->forks[index++], NULL))
			return (NULL);
	pthread_mutex_init(&locks->write, NULL);
	pthread_mutex_init(&locks->meal, NULL);
	pthread_mutex_init(&locks->dead, NULL);
	return (locks);
}

int	destroy_mutex(t_locks *locks, int nb_phi)
{
	int	index;

	index = 0;
	while (index < nb_phi)
		pthread_mutex_destroy(&locks->forks[index++]);
	pthread_mutex_destroy(&locks->write);
	pthread_mutex_destroy(&locks->meal);
	pthread_mutex_destroy(&locks->dead);
	free(locks->forks);
	free(locks);
	return (0);
}

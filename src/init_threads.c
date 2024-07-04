/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:49:10 by tforster          #+#    #+#             */
/*   Updated: 2024/07/04 16:45:40 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	*init_philo(t_args *args, t_locks *locks, int index)
{
	int		total;
	t_philo	*philo;

	total = args->nb_philos;
	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->id = index + 1;
	gettimeofday(&philo->t0, NULL);
	philo->eat = 0;
	philo->args = args;
	philo->l_fork = &locks->forks[index % total];
	philo->r_fork = &locks->forks[(index + 1) % total];
	philo->write = &locks->write;
	philo->dead = &locks->dead;
	return (philo);
}

// t_philo	*init_threads(t_args *args, t_locks *locks)
pthread_t	*init_threads(t_args *args, t_locks *locks)
{
	int		total;
	int		index;
	t_philo	*philo;
	pthread_t	*thread;

	total = args->nb_philos;
	// philo = malloc(args->nb_philos * sizeof(t_philo));
	thread = malloc(total * sizeof(pthread_t));
	// index = 0;
	// while (index < total)
	// {
	// 	philo[index].id = 1 + index;
	// 	philo[index].born = get_time();
	// 	philo[index].args = args;
	// 	philo[index].l_fork = locks->forks[index % total];
	// 	philo[index].r_fork = locks->forks[(index + 1) % total];
	// 	index++;
	// }

	index = 0;
	while (index < total)
	{
		// args->ctrl = malloc(sizeof(int));
		// args->ctrl = &index;
		// printf("CTRL [%d]\n", *args->ctrl);
		// if (pthread_create(&philo[index].thread, NULL, starve, (void *) init_philo(args, locks, index)))
		// 	return (NULL);
		if (pthread_create(&thread[index], NULL, greedy_phi, (void *) init_philo(args, locks, index)))
			return (NULL);
		index++;
	}
	// return (philo);
	return (thread);
}

// int	join_threads(t_args *args, pthread_t *philos)
// int	join_threads(t_philo *philo, int nb_philos)
int	join_threads(pthread_t *thread, int nb_philos)
{
	int	index;

	index = 0;
	while (index < nb_philos)
	{
		// if (pthread_join(philo[index++].thread, NULL))
		if (pthread_join(thread[index++], NULL))
			return (1);
	}
	return (0);
}

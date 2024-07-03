/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:49:10 by tforster          #+#    #+#             */
/*   Updated: 2024/07/03 19:48:09 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*starve(void *args)
{
	t_args	*philos;

	philos = (t_args *) args;
	printf("START THREAD!\n");
	return (NULL);
}

t_philo	*init_philo(t_args *args, t_locks *locks, int index)
{
	int		total;
	t_philo	*philo;

	total = args->nb_philos;
	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->id = 1 + index;
	philo->args = args;
	philo[index].l_fork = locks->forks[index % total];
	philo[index].r_fork = locks->forks[(index + 1) % total];
	return (philo);
}

t_philo	*init_threads(t_args *args, t_locks *locks)
// pthread_t	*init_threads(t_args *args, t_locks *locks)
{
	int		total;
	int		index;
	t_philo	*philo;
	pthread_t	*thread;

	total = args->nb_philos;
	philo = malloc(args->nb_philos * sizeof(t_philo));
	// thread = malloc(total * sizeof(pthread_t));
	index = 0;
	while (index < total)
	{
		philo[index].id = 1 + index;
		philo[index].born = get_time();
		philo[index].args = args;
		philo[index].l_fork = locks->forks[index % total];
		philo[index].r_fork = locks->forks[(index + 1) % total];
		index++;
	}

	index = 0;
	while (index < total)
	{
		// args->ctrl = malloc(sizeof(int));
		// args->ctrl = &index;
		// printf("CTRL [%d]\n", *args->ctrl);
		if (pthread_create(&philo[index].thread, NULL, starve, (void *) args))
			return (NULL);
		index++;
	}
	return (philo);
	// return (thread);
}

// int	join_threads(t_args *args, pthread_t *philos)
int	join_threads(t_philo *philo, int nb_philos)
{
	int	index;

	index = 0;
	while (index < nb_philos)
	{
		if (pthread_join(philo[index++].thread, NULL))
			return (1);
	}
	return (0);
}

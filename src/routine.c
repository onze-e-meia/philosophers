/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:42:54 by tforster          #+#    #+#             */
/*   Updated: 2024/07/07 20:37:39 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*lone_phi(t_phi *phi);
static void	gluttony(t_phi *phi, int *count);
static void	sloth(t_phi *phi, int *count);
static int	check_dead(t_phi *phi);

void	*routine(void *args)
{
	t_phi	*phi;
	bool	loop;
	int		count;

	phi = (t_phi *) args;
	if (phi->args->nb_phi == 1)
		return (lone_phi(phi));
	loop = (phi->args->nb_meals == -1);
	count = 0;
	while (count < 2 * phi->args->nb_meals || loop)
	{
		if ((phi->id + count) % 2 != 0)
			gluttony(phi, &count);
		else
			sloth(phi, &count);
		pthread_mutex_lock(phi->dead);
		if (check_dead(phi))
			return (NULL);
	}
	pthread_mutex_lock(phi->meal);
	phi->args->fed_phi++;
	pthread_mutex_unlock(phi->meal);
	return (NULL);
}

static void	*lone_phi(t_phi *phi)
{
	pthread_mutex_lock(phi->l_fork);
	timestamp(phi, FORK);
	usleep(phi->args->t_live);
	pthread_mutex_unlock(phi->l_fork);
	return (NULL);
}

static void	gluttony(t_phi *phi, int *count)
{
	pthread_mutex_lock(phi->l_fork);
	timestamp(phi, FORK);
	pthread_mutex_lock(phi->r_fork);
	timestamp(phi, FORK);
	pthread_mutex_lock(phi->meal);
	phi->time = timestamp(phi, EAT);
	phi->eaten++;
	pthread_mutex_unlock(phi->meal);
	usleep(phi->args->t_eat);
	pthread_mutex_unlock(phi->l_fork);
	pthread_mutex_unlock(phi->r_fork);
	timestamp(phi, SLEEP);
	usleep(phi->args->t_sleep);
	timestamp(phi, THINK);
	(*count)++;
}

static void	sloth(t_phi *phi, int *count)
{
	(void) phi;
	usleep(500);
	(*count)++;
}

static int	check_dead(t_phi *phi)
{
	bool	status;

	status = phi->args->dead;
	pthread_mutex_unlock(phi->dead);
	return (status);
}

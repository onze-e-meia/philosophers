/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:42:54 by tforster          #+#    #+#             */
/*   Updated: 2024/07/06 23:05:08 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		check_dead(t_phi *phi);

void	*routine(void *args)
{
	int		count;
	t_usec	dt;
	t_tval	tval;
	t_phi	*phi;

	phi = (t_phi *) args;
	dt = 0;
	count = 0;

	bool	loop;
	loop = false;
	if (phi->args->nb_meals == -1)
		loop = true;

	while (count < 2 * phi->args->nb_meals || loop)
	{
		if ((phi->id + count) % 2 != 0)
		{
			pthread_mutex_lock(phi->l_fork);
			check_state(phi, false, FORK);

			pthread_mutex_lock(phi->r_fork);
			check_state(phi, false, FORK);

			pthread_mutex_lock(phi->meal);
			phi->eaten++;
			pthread_mutex_unlock(phi->meal);

			// START EATING, ZERO TIME
			phi->time = check_state(phi, false, EAT);
			// if (phi->args->live < phi->args->eat)
			// {
			// 	usleep(phi->args->live);
			// 	check_state(phi, true, DIE);
			// 	pthread_mutex_unlock(phi->r_fork);
			// 	pthread_mutex_unlock(phi->l_fork);
			// 	return (NULL);
			// }

			usleep(phi->args->t_eat);
			pthread_mutex_unlock(phi->r_fork);
			pthread_mutex_unlock(phi->l_fork);
			// END EATING

			// START SLEEPING, ZERO TIME
			check_state(phi, false, SLEEP);
			// printf(">> id[%d] delta[%ld]\n", phi->id, phi->time);
			// if (phi->args->live < phi->args->sleep + phi->time)
			// {
			// 	usleep(phi->args->live -  phi->args->eat);
			// 	check_state(phi, true, DIE);
			// 	return (NULL);
			// }

			usleep(phi->args->t_sleep);
			// END SLEEPING, ZERO TIME

			// START THINKING
			check_state(phi, false, THINK);
			// printf(">> id[%d] delta[%ld]\n", phi->id, dt);
			count++;
			// END THINKING
		}
		else
		{
			// usleep(phi->args->t_eat - 1000);
			usleep(10);
			count++;
		}
		pthread_mutex_lock(phi->dead);
		if (check_dead(phi))
		{
			// printf(">>>[%d] TRHEAD END BY DEAD  <<<\n", phi->id);
			return (NULL);
		}
	}
	pthread_mutex_lock(phi->meal);
	phi->args->fed_phi++;
	pthread_mutex_unlock(phi->meal);
	// printf(">>>[%d] TRHEAD END BY LOOP <<<\n", phi->id);
	return (NULL);
}

int	check_dead(t_phi *phi)
{
	bool	status;

	status = phi->args->dead;
	pthread_mutex_unlock(phi->dead);
	return (status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grim_reaper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:22:04 by tforster          #+#    #+#             */
/*   Updated: 2024/07/07 17:39:01 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	dead_alive(t_locks *locks, t_phi *phi)
{
	t_usec			usec;
	bool			state;
	const t_print	func[2] = {do_nothing, print_state};

	usec = usec_time();
	pthread_mutex_lock(&locks->meal);
	state = (usec - phi->time > phi->args->t_live);
	state = !(phi->eaten == phi->args->nb_meals) * state;
	pthread_mutex_unlock(&locks->meal);
	pthread_mutex_lock(phi->dead);
	func[state](phi, state, DIE, usec);
	pthread_mutex_unlock(phi->dead);
	return (state);
}

void	grim_reaper(t_args *args, t_locks *locks, t_phi *phi)
{
	int		index;

	while (true)
	{
		index = 0;
		while (index < args->nb_phi)
		{
			if (dead_alive(locks, &phi[index]))
				return ;
			index++;
		}
		pthread_mutex_lock(&locks->meal);
		if (args->fed_phi == args->nb_phi)
		{
			pthread_mutex_unlock(&locks->meal);
			return ;
		}
		pthread_mutex_unlock(&locks->meal);
	}
}

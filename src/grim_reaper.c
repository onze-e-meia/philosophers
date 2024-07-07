/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grim_reaper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:22:04 by tforster          #+#    #+#             */
/*   Updated: 2024/07/07 14:48:37 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	dead_alive(t_locks *locks, t_phi *phi)
{
	t_usec	usec;
	bool	state;
	void	(*func[2])(t_phi *, bool, char *, t_usec);

	func[false] = do_nothing;
	func[true] = print_state;

	usec = usec_time();
	// state = (usec - phi->time > phi->args->t_live) * true + (usec - phi->time <= phi->args->t_live) * false;
	state = (usec - phi->time > phi->args->t_live);

	pthread_mutex_lock(&locks->meal);
	state = !(phi->eaten == phi->args->nb_meals) * state;
	// if (phi->eaten == phi->args->nb_meals)
	// 	state = false;
	pthread_mutex_unlock(&locks->meal);

	// printf("%ds[%d] log[%ld] del[%ld] l[%ld]\n", phi->id, state, usec - phi->args->t0, (usec - phi->time), phi->args->live);
	pthread_mutex_lock(phi->dead);
	func[state](phi, state, DIE, usec);
	pthread_mutex_unlock(phi->dead);
	// printf("ID[%d] STATE[%d]%d\n", phi->id, phi->args->dead, state);
	return (state);
}

void	grim_reaper(t_args *args, t_locks *locks, t_phi *phi)
{
	int		index;

	// printf("LOOPS [%d][%d]\n", phi[0].id, phi[1].id);
	while (true)
	{
		index = 0;
		while (index < args->nb_phi)
		{
			if (dead_alive(locks, &phi[index]))
			{
				// printf(">>>> ID[%d] STATE[%d]\n", phi[index].id, phi[index].args->dead);
				// printf(">>> EXIT BY DEAD PHI<<<\n");
				return ;
			}
			index++;
		}
		pthread_mutex_lock(&locks->meal);
		if (args->fed_phi == args->nb_phi)
		{
			pthread_mutex_unlock(&locks->meal);
			// printf(">>> EXIT BY MAX MEALS <<<\n");
			return ;
		}
		pthread_mutex_unlock(&locks->meal);
	}
	// return (grim_reaper(args, locks, phi));
}

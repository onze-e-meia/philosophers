/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:35:16 by tforster          #+#    #+#             */
/*   Updated: 2024/07/07 15:30:21 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_usec	timestamp(t_phi *phi, char *msg)
{
	t_usec	usec;
	t_tval	tval;
	void	(*func[2])(t_phi *, bool, char *, t_usec);

	func[false] = print_state;
	func[true] = do_nothing;
	gettimeofday(&tval, NULL);
	usec = usec_time();
	pthread_mutex_lock(phi->dead);
	func[phi->args->dead](phi, false, msg, usec);
	pthread_mutex_unlock(phi->dead);
	return (usec);
}

void	print_state(t_phi *phi, bool state, char *msg, t_usec usec)
{
	t_usec	dt;

	dt = (usec - phi->args->t0) * 0.001;
	phi->args->dead = state;
	pthread_mutex_lock(phi->write);
	printf(msg, dt, phi->id);
	pthread_mutex_unlock(phi->write);
}

void	do_nothing(t_phi *phi, bool state, char *msg, t_usec usec)
{
	(void) phi;
	(void) state;
	(void) msg;
	(void) usec;
	return ;
}

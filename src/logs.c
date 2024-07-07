/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:35:16 by tforster          #+#    #+#             */
/*   Updated: 2024/07/07 17:49:05 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_usec	timestamp(t_phi *phi, char *msg)
{
	t_usec			usec;
	const t_print	func[2] = {print_state, do_nothing};

	pthread_mutex_lock(phi->dead);
	usec = usec_time();
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

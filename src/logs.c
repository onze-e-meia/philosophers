/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:35:16 by tforster          #+#    #+#             */
/*   Updated: 2024/07/06 18:14:38 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_usec	delta_t(t_usec t0, t_usec t1);


t_usec	check_state(t_phi *phi, bool state, char *msg)
{
	t_usec	usec;
	t_tval	tval;
	void	(*func[2])(t_phi *, bool, char *, t_usec);

	func[false] = print_state;
	func[true] = do_nothing;

	gettimeofday(&tval, NULL);
	usec = usec_time();
	pthread_mutex_lock(phi->dead);
	func[phi->args->dead](phi, state, msg, usec);
	pthread_mutex_unlock(phi->dead);
	return (usec);
}

void	print_state(t_phi *phi, bool state, char *msg, t_usec usec)
{
	t_usec	dt;

	dt = delta_t(phi->args->t0, usec) * 0.001;
	phi->args->dead = state;
	pthread_mutex_lock(phi->write);
	printf(msg, dt, phi->id);
	pthread_mutex_unlock(phi->write);
}

void	do_nothing(t_phi *phi, bool state, char *msg, t_usec usec)
{
	return ;
}

t_usec	delta_t(t_usec t0, t_usec t1)
{
	return (t1 - t0);
}

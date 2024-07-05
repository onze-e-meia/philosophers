/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:42:54 by tforster          #+#    #+#             */
/*   Updated: 2024/07/05 17:48:35 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_usec	check_state(t_phi *phi, bool state, char *msg);
static t_usec	delta_t(t_tval *t0, t_tval *t1);
int		check_dead(t_phi *phi);
void	print_dead(t_phi *phi, char *msg);


void	*greedy_phi(void *args)
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
	if (phi->args->times == -1)
		loop = true;

	while (count < phi->args->times || loop)
	{

		pthread_mutex_lock(phi->l_fork);
		check_state(phi, false, FORK);

		pthread_mutex_lock(phi->r_fork);
		check_state(phi, false, FORK);

		// gettimeofday(&tval, NULL);
		// dt = tval.tv_sec * 1000000 + tval.tv_usec - dt;
		// printf(">> id[%d] delta[%ld]\n", phi->id, dt);

		// START EATING, ZERO TIME
		dt = check_state(phi, false, EAT);
		if (phi->args->live < phi->args->eat)
		{
			usleep(phi->args->live);
			check_state(phi, true, DIE);

			pthread_mutex_unlock(phi->r_fork);
			pthread_mutex_unlock(phi->l_fork);
			return (NULL);
		}
		usleep(phi->args->eat);
		pthread_mutex_unlock(phi->r_fork);
		pthread_mutex_unlock(phi->l_fork);
		// END EATING

		// START SLEEPING, ZERO TIME
		dt = check_state(phi, false, SLEEP) - dt;
		if (phi->args->live < phi->args->sleep +  dt)
		{
			usleep(phi->args->live -  phi->args->eat);
			check_state(phi, true, DIE);
			return (NULL);
		}
		usleep(phi->args->sleep);
		// END SLEEPING, ZERO TIME
		dt = check_state(phi, false, THINK) - dt;
		// printf(">> id[%d] delta[%ld]\n", phi->id, dt);


		count++;
		phi->eat++;
	}
	free(phi);
	return (NULL);
}

t_usec	time_to_die(t_phi *phi)
{
	t_usec	die;

	usleep(phi->args->live);
		check_state(phi, true, DIE);

	pthread_mutex_unlock(phi->r_fork);
	pthread_mutex_unlock(phi->l_fork);
	return (0);
}

void	print_state(t_phi *phi, bool state, char *msg, t_usec u_sec)
{
	phi->args->dead = state;
	pthread_mutex_lock(phi->write);
	printf(msg, u_sec, phi->id);
	pthread_mutex_unlock(phi->write);
}

void	do_nothing(t_phi *phi, bool state, char *msg, t_usec u_sec)
{
	return ;
}

t_usec	check_state(t_phi *phi, bool state, char *msg)
{
	t_usec	u_sec;
	t_tval	tval;
	void	(*func[2])(t_phi *, bool, char *, t_usec);

	func[false] = print_state;
	func[true] = do_nothing;

	gettimeofday(&tval, NULL);
	u_sec = delta_t(&phi->t0, &tval);
	// printf(">> id[%d] delta[%ld]\n", phi->id, u_sec);
	pthread_mutex_lock(phi->dead);
	func[phi->args->dead](phi, state, msg, 0.001 * u_sec);
	pthread_mutex_unlock(phi->dead);
	return (u_sec);
}

int	check_dead(t_phi *phi)
{
	pthread_mutex_unlock(phi->dead);
	return (phi->args->dead);
}

t_usec	delta_t(t_tval *t0, t_tval *t1)
{
	// return (((t1->tv_sec * 1000000 + t1->tv_usec) - (t0->tv_sec * 1000000 + t0->tv_usec)) * 0.001);
	return ((t1->tv_sec * 1000000 + t1->tv_usec) - (t0->tv_sec * 1000000 + t0->tv_usec));
}

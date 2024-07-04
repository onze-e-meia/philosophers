/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:42:54 by tforster          #+#    #+#             */
/*   Updated: 2024/07/04 20:37:09 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	print_state(t_phi *phi, bool state, char *msg);
static suseconds_t	delta_t(t_time *t0, t_time *t1);
int		check_dead(t_phi *phi);
void	print_dead(t_phi *phi, char *msg);


void	*greedy_phi(void *args)
{
	int		count;
	t_phi	*phi;

	phi = (t_phi *) args;

	count = 0;
	while (!phi->args->dead && count < phi->args->times)
	// pthread_mutex_lock(phi->dead);
	// while (!check_dead(phi) && count < phi->args->times)
	{
		// printf("ID[%d] COUNT[%d] EAT[%d] [%d]\n", phi->id, count, phi->eat, (phi->id + phi->eat) % 2);
		// pthread_mutex_lock(phi->dead);
		// if (!check_dead(phi) && (phi->id + phi->eat) % 2 != 0)
		if ((phi->id + phi->eat) % 2 != 0)
		{
			pthread_mutex_lock(phi->l_fork);
			print_state(phi, false, FORK);

			pthread_mutex_lock(phi->r_fork);
			print_state(phi, false, FORK);

			// START EATING, ZERO TIME
			print_state(phi, false, EAT);

			// pthread_mutex_lock(phi->dead);
			// if (check_dead(phi))
			// 	return (NULL);
			// else if (phi->args->live < phi->args->eat)
			// {
			// 	usleep(phi->args->live);

			// 	pthread_mutex_unlock(phi->dead);
			// 	print_state(phi, true, DIE);
			// 	phi->args->dead = true;
			// 	// print_dead(phi, DIE);
			// 	pthread_mutex_unlock(phi->dead);

			// 	pthread_mutex_unlock(phi->l_fork);
			// 	pthread_mutex_unlock(phi->r_fork);
			// 	return (NULL);
			// }

			usleep(phi->args->eat);
			pthread_mutex_unlock(phi->l_fork);
			pthread_mutex_unlock(phi->r_fork);

			print_state(phi, false, SLEEP);
			usleep(phi->args->sleep);



			count++;
			phi->eat++;
		}
		else
		{
			// count--;
			usleep(5);
			phi->eat++;
			// return (NULL);
		}
		// count++;
		// phi->eat--;
	}

	free(phi);
	return (NULL);
}

// suseconds_t	time_to_die(t_time *time, suseconds_t *live)
// {
// 	suseconds_t	die;

// }

// void	print_state(t_phi *phi, t_time *t, pthread_mutex_t *write, char *msg)
void	print_state(t_phi *phi, bool state, char *msg)
{
	suseconds_t	m_sec;
	t_time		time;

	pthread_mutex_lock(phi->dead);
	// phi->args->dead = phi->args->dead ^ state;
	// phi->args->dead = (!phi->args->dead) * state;
	// if (state)
	// phi->args->dead = state;
	gettimeofday(&time, NULL);
	if (!check_dead(phi))
	{
		m_sec = delta_t(&phi->t0, &time);
		pthread_mutex_lock(phi->write);
		printf(msg, m_sec, phi->id);
		pthread_mutex_unlock(phi->write);
	}
}

void	print_dead(t_phi *phi, char *msg)
{
	suseconds_t	m_sec;
	t_time		time;

	// phi->args->dead = phi->args->dead ^ state;
	// phi->args->dead = (!phi->args->dead) * state;
	// if (state)
	// phi->args->dead = state;
	gettimeofday(&time, NULL);
	m_sec = delta_t(&phi->t0, &time);
	pthread_mutex_lock(phi->write);
	printf(msg, m_sec, phi->id);
	pthread_mutex_unlock(phi->write);
}

int	check_dead(t_phi *phi)
{
	// if (phi->args->dead == true)
	// {
	// 	pthread_mutex_unlock(phi->dead);
	// 	return (1);
	// }
	// pthread_mutex_unlock(phi->dead);
	// return (0);
	pthread_mutex_unlock(phi->dead);
	return (phi->args->dead);
}

suseconds_t	delta_t(t_time *t0, t_time *t1)
{
	// suseconds_t	sec;
	// suseconds_t	m_sec;

	// sec = t1->tv_sec - t0->tv_sec;
	// m_sec = t1->tv_usec - t0->tv_usec;
	// if (m_sec < 0)
	// {
	// 	sec -= 1;
	// 	m_sec += 1000000;
	// }
	// return ((sec * 100000 + m_sec) * 0.001);
	return (((t1->tv_sec * 1000000 + t1->tv_usec) - (t0->tv_sec * 1000000 + t0->tv_usec)) * 0.001);
}

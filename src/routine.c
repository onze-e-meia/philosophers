/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:42:54 by tforster          #+#    #+#             */
/*   Updated: 2024/07/04 16:48:58 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	print_status(t_phi *phi, t_time *t, pthread_mutex_t *write, char *msg);
static suseconds_t	delta_t(t_time *t0, t_time *t1);

void	*greedy_phi(void *args)
{
	int		count;
	t_phi	*phi;

	phi = (t_phi *) args;

	count = 0;
	while (!phi->args->dead && count < phi->args->times)
	{
		t_time	t[2];
		t_time	t_left;
		t_time	t_right;

		if ((phi->id + phi->eat) % 2 != 0)
		{
			pthread_mutex_lock(phi->l_fork);
			gettimeofday(&t[LFT], NULL);
			print_status(phi, &t[LFT], phi->write, FORK);

			pthread_mutex_lock(phi->r_fork);
			gettimeofday(&t[RGT], NULL);
			print_status(phi, &t[RGT], phi->write, FORK);

			gettimeofday(&t[RGT], NULL);
			print_status(phi, &t[RGT], phi->write, EAT);

			usleep(phi->args->eat);
			pthread_mutex_unlock(phi->l_fork);
			pthread_mutex_unlock(phi->r_fork);
		}
		count++;
	}

	free(phi);
	return (NULL);
}

void	print_status(t_phi *phi, t_time *t, pthread_mutex_t *write, char *msg)
{
	suseconds_t m_sec;

	m_sec = delta_t(&phi->t0, t);
	printf(msg, m_sec, phi->id);
}

suseconds_t	delta_t(t_time *t0, t_time *t1)
{
	suseconds_t	sec;
	suseconds_t	m_sec;

	sec = t1->tv_sec - t0->tv_sec;
	m_sec = t1->tv_usec - t0->tv_usec;
	if (m_sec < 0)
	{
		sec -= 1;
		m_sec += 1000000;
	}
	return ((sec * 100000 + m_sec) * 0.001);
}

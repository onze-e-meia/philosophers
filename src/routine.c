/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:42:54 by tforster          #+#    #+#             */
/*   Updated: 2024/07/04 16:46:02 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	print_status(t_philo *philo, t_time *t, pthread_mutex_t *write, char *msg);
static suseconds_t	delta_t(t_time *t0, t_time *t1);

void	*greedy_phi(void *args)
{
	int		count;
	t_philo	*philo;

	philo = (t_philo *) args;

	count = 0;
	while (!philo->args->dead && count < philo->args->times)
	{
		t_time	t[2];
		t_time	t_left;
		t_time	t_right;

		if ((philo->id + philo->eat) % 2 != 0)
		{
			pthread_mutex_lock(philo->l_fork);
			gettimeofday(&t[LFT], NULL);
			print_status(philo, &t[LFT], philo->write, FORK);

			pthread_mutex_lock(philo->r_fork);
			gettimeofday(&t[RGT], NULL);
			print_status(philo, &t[RGT], philo->write, FORK);

			gettimeofday(&t[RGT], NULL);
			print_status(philo, &t[RGT], philo->write, EAT);

			usleep(philo->args->eat);
			pthread_mutex_unlock(philo->l_fork);
			pthread_mutex_unlock(philo->r_fork);
		}
		count++;
	}

	free(philo);
	return (NULL);
}

void	print_status(t_philo *philo, t_time *t, pthread_mutex_t *write, char *msg)
{
	suseconds_t m_sec;

	m_sec = delta_t(&philo->t0, t);
	printf(msg, m_sec, philo->id);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:36:34 by tforster          #+#    #+#             */
/*   Updated: 2024/07/04 19:55:21 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

# define RED "\033[0;31m"
# define GRN "\033[0;32m"
# define YLW "\033[0;33m"
# define BLU "\033[0;34m"
# define MAG "\033[0;35m"
# define CYN "\033[0;36m"
# define RST "\033[0m"

# define ERR01 "Argument is empty.\n"
# define ERR02 "Argument is a negative number.\n"
# define ERR03 "Argument is not a number.\n"
# define ERR04 "Argument time (micro_s) is bigger then 16 minutes.\n"
# define ERR05 "Argument times to eat is bigger then 999999999.\n"

# define FORK " %ld %d\033[0;35m has taken a fork\033[0m\n"
# define EAT " %ld %d\033[0;33m is eating\033[0m\n"
# define SLEEP " %ld %d\033[0;32m is sleeping\033[0m\n"
# define THINK " %ld %d\033[0;34m is thinking\033[0m\n"
# define DIE " %ld %d\033[0;31m died\033[0m\n"

# define LFT 0
# define RGT 1

typedef enum e_arg_error
{
	ARG_OK = 0,
	EMPTY_ARG,
	NEG_ARG,
	NOT_DIGIT,
	TOO_BIG,
}	t_arg_error;

typedef struct timeval t_time;

typedef struct s_args
{
	int				nb_philos;
	suseconds_t		live;
	suseconds_t		eat;
	suseconds_t		sleep;
	int				times;
	bool			dead;
}					t_args;

typedef struct s_locks
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	pthread_mutex_t	dead;
}					t_locks;

typedef struct s_philo
{
	int				id;
	t_time			t0;
	int				eat;
	t_args			*args;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*write;
	pthread_mutex_t	*dead;
}					t_phi;


suseconds_t	get_time();
void		put_str(int fd, char *str);
int			is_digit(int ch);
int			atoi(const char *nbr);

int			init_args(int argc, char **argv, t_args *args);

t_locks		*init_mutex(int nb_philos);
int			destroy_mutex(t_locks *locks, int nb_philos);

pthread_t	*init_threads(t_args *args, t_locks *locks);
int			join_threads(pthread_t *thread, int nb_philos);

void		*greedy_phi(void *args);

#endif

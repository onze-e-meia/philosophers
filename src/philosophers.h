/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:36:34 by tforster          #+#    #+#             */
/*   Updated: 2024/07/07 19:05:29 by tforster         ###   ########.fr       */
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

# define ERR0 "Argument is empty.\n"
# define ERR1 "Argument is a negative number.\n"
# define ERR2 "Argument is not a number.\n"
# define ERR3 "Argument time (micro_s) is bigger then 16 minutes.\n"
# define ERR4 "Argument times to eat is bigger then 999999999.\n"
# define ERR5 "Argument must bigger then 60.\n"

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
	TOO_SMAL,
}	t_arg_error;

typedef struct timeval	t_tval;
typedef suseconds_t		t_usec;
typedef pthread_t		t_thread;
typedef pthread_mutex_t	t_mutex;
typedef struct s_args	t_args;
typedef struct s_locks	t_locks;
typedef struct s_phi	t_phi;
typedef void			(*t_sin)(t_phi *, int *);
typedef void			(*t_print)(t_phi *, bool, char *, t_usec);

struct s_args
{
	int			nb_phi;
	int			fed_phi;
	t_usec		t_live;
	t_usec		t_eat;
	t_usec		t_sleep;
	t_usec		t0;
	int			nb_meals;
	bool		dead;
};

struct s_locks
{
	t_mutex		*forks;
	t_mutex		write;
	t_mutex		meal;
	t_mutex		dead;
};

struct s_phi
{
	int			id;
	t_tval		t0;
	t_usec		time;
	int			eaten;
	t_args		*args;
	t_mutex		*l_fork;
	t_mutex		*r_fork;
	t_mutex		*write;
	t_mutex		*meal;
	t_mutex		*dead;
};

/* Utiils */
t_usec			usec_time(void);
void			put_str(int fd, char *str);
int				is_digit(int ch);
int				atoi(const char *nbr);

/* INIT ARGS */
int				init_args(int argc, char **argv, t_args *args);
t_locks			*init_mutex(int nb_phi);
int				destroy_mutex(t_locks *locks, int nb_phi);

/* INIT PHILOS AND THREADS */
t_phi			*init_phi(t_args *args, t_locks *locks);
t_thread		*init_threads(t_args *args, t_phi *phi);
int				join_threads(t_thread *thread, t_phi *phi, int nb_phi);

/* ROUTINE AND MONITORING */
void			*routine(void *args);
void			grim_reaper(t_args *args, t_locks *locks, t_phi *phi);

/* LOGS */
t_usec			timestamp(t_phi *phi, char *msg);
void			print_state(t_phi *phi, bool state, char *msg, t_usec u_sec);
void			do_nothing(t_phi *phi, bool state, char *msg, t_usec u_sec);

#endif

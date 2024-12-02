/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esekouni <esekouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 16:08:37 by esekouni          #+#    #+#             */
/*   Updated: 2023/05/13 12:12:42 by esekouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <sys/wait.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/time.h>
# include <signal.h>
# include <pthread.h>
# include <unistd.h>
# include <semaphore.h>
# include <limits.h>

typedef struct s_philo
{
	int				d;
	unsigned long	time;
	int				nmber_philo;
	int				time_die;
	int				argc;
	int				time_eat;
	int				time_sleep;
	int				numb_times_eat;
	sem_t			*sem;
	sem_t			*eat_time;
	sem_t			*eat;
	sem_t			*tmp;
	sem_t			*tmp2;
	sem_t			*print;
	int				status;
}t_philo;

typedef struct s_philosopher
{
	int				index;
	int				numb_eat;
	unsigned long	tmp;
	unsigned long	tmp2;
	unsigned long	time;
	t_philo			*ph;
	pthread_t		t;
	pid_t			id;
	pid_t			rewaitpid;
}t_philosopher;
long			ft_atoi(char *ch);
int				check_caractere(char *av);
int				check_args(char **argv, int argc, t_philo *ph);
int				check_arg6(char *av);
unsigned long	time_work(void);
void			semaphore_init(t_philo *ph);
t_philosopher	*philo_create(t_philo *ph, pthread_t *phi);
void			*th_rotine(void *ph);
void			rotine(t_philosopher *p);
void			rotine_2(t_philosopher *p, int *eat);
void			*tth_rotine(void *ph);
void			ft_kill(t_philosopher *p);
void			creation_process(t_philosopher *p);
void			check_eat_number(t_philosopher *p);
void			ft_print(char *ch, unsigned long time, t_philosopher *p);
void			ft_free(t_philosopher *p);

#endif
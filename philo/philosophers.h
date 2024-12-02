/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esekouni <esekouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 21:24:04 by esekouni          #+#    #+#             */
/*   Updated: 2023/05/12 16:01:28 by esekouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
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
	int				*numb_eat;
	int				numb_times_eat;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	var;
	pthread_mutex_t	var1;
	pthread_mutex_t	var2;
	pthread_mutex_t	var3;
}t_philo;

typedef struct s_philosopher
{
	int				index;
	unsigned long	tmp;
	unsigned long	tmp2;
	unsigned long	time;
	pthread_mutex_t	mutex_print;
	pthread_t		t;
	t_philo			*ph;
}t_philosopher;

long			ft_atoi(char *ch);
unsigned long	time_worck(void);
int				check_philo(t_philosopher *p);
int				ft_join_philo(t_philosopher *p);
int				check_arg(char **av, int ac, t_philo *ph);
void			ft_print(char *ch, unsigned long time, t_philosopher *p);
int				check_eat_time(t_philosopher *p);
int				check_number_eat_times(int *arr, int n, int eat_times);
void			mutex_init(t_philo *ph, t_philosopher *p);
int				rotine1(t_philosopher *p);
int				rotine2(t_philosopher *p);
void			ft_free(t_philosopher *p);

#endif
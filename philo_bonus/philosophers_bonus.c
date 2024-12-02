/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esekouni <esekouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:10:50 by esekouni          #+#    #+#             */
/*   Updated: 2023/05/13 15:03:11 by esekouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	*th_rotine(void *ph)
{
	t_philosopher	*p;

	p = (t_philosopher *)ph;
	while (1)
	{
		sem_wait(p->ph->tmp);
		if (time_work() - p->tmp >= (unsigned long)p->ph->time_die)
		{
			sem_post(p->ph->tmp);
			sem_wait(p->ph->print);
			printf("%ld %d died\n", time_work() - p->tmp, p->index + 1);
			exit(1);
		}
		sem_post(p->ph->tmp);
	}
	return (NULL);
}

void	rotine(t_philosopher *p)
{
	int	eat;

	eat = 0;
	while (1)
	{
		ft_print("is thinking", (time_work() - p->time), p);
		sem_wait(p->ph->sem);
		ft_print("has taken a fork", (time_work() - p->time), p);
		sem_wait(p->ph->sem);
		ft_print("has taken a fork", (time_work() - p->time), p);
		sem_wait(p->ph->tmp);
			p->tmp = time_work();
		sem_post(p->ph->tmp);
		ft_print("is eating", (time_work() - p->time), p);
		while (time_work() - p->tmp <= (unsigned long)p->ph->time_eat)
			usleep(200);
		rotine_2(p, &eat);
		sem_post(p->ph->sem);
		sem_post(p->ph->sem);
		p->tmp2 = time_work();
		ft_print("is sleeping", (time_work() - p->time), p);
		while (time_work() - p->tmp2 <= (unsigned long)p->ph->time_sleep)
			usleep(200);
	}
}

void	*tth_rotine(void *ph)
{
	t_philosopher	*p;

	p = (t_philosopher *)ph;
	check_eat_number(p);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_philo			*ph;
	pthread_t		phi;
	t_philosopher	*p;

	if (argc == 5 || argc == 6)
	{
		ph = malloc(sizeof(t_philo));
		if (check_args(argv, argc, ph) == 0)
		{
			free(ph);
			return (1);
		}
		p = philo_create(ph, &phi);
		pthread_join(phi, NULL);
		ft_kill(p);
		ft_free(p);
	}
	else
		printf("invalid arguments\n");
	return (0);
}

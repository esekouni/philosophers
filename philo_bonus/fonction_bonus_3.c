/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction_bonus_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esekouni <esekouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 13:06:17 by esekouni          #+#    #+#             */
/*   Updated: 2023/05/13 12:02:33 by esekouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

t_philosopher	*philo_create(t_philo *ph, pthread_t *phi)
{
	int				i;
	t_philosopher	*p;

	i = 0;
	semaphore_init(ph);
	ph->status = 0;
	p = malloc(sizeof(t_philosopher) * ph->nmber_philo);
	while (i < ph->nmber_philo)
	{
		p[i].index = i;
		p[i].numb_eat = 0;
		p[i].ph = ph;
		p[i].time = time_work();
		p[i].tmp = time_work();
		p[i].id = -1;
		i++;
	}
	creation_process(p);
	if (ph->argc == 6)
		pthread_create(phi, NULL, tth_rotine, p);
	p->rewaitpid = waitpid(-1, &(p->ph->status), 0);
	sem_post(p->ph->eat);
	return (p);
}

void	ft_kill(t_philosopher *p)
{
	int	i;

	i = 0;
	while (i < p->ph->nmber_philo)
	{
		if (p[i].id != p->rewaitpid)
		{
			if (kill(p[i].id, SIGKILL) != 0)
				printf("Error kill\n");
		}
		i++;
	}
}

void	ft_free(t_philosopher *p)
{
	sem_close(p->ph->sem);
	sem_close(p->ph->tmp);
	sem_close(p->ph->print);
	sem_close(p->ph->eat);
	sem_close(p->ph->eat_time);
	free(p->ph);
	free(p);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esekouni <esekouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:39:10 by esekouni          #+#    #+#             */
/*   Updated: 2023/05/13 15:05:14 by esekouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philosophers.h"

int	check_philo(t_philosopher *p)
{
	int	i;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&(p->ph->var2));
		if ((time_worck() - p[i].tmp >= (unsigned long)p->ph->time_die))
		{
			pthread_mutex_lock(&(p->ph->var));
			p->ph->d = 0;
			pthread_mutex_unlock(&(p->ph->var));
			pthread_mutex_lock(&(p->mutex_print));
			printf("%ld %d died\n", (time_worck() - p->ph->time), i + 1);
			pthread_mutex_unlock(&(p->mutex_print));
			pthread_mutex_unlock(&(p->ph->var2));
			return (0);
		}
		pthread_mutex_unlock(&(p->ph->var2));
		if (check_eat_time(p) == 0)
			return (0);
		i = (i + 1) % (p->ph->nmber_philo);
	}
}

void	*rotine(void *p)
{
	t_philosopher	*ph1;

	ph1 = (t_philosopher *)p;
	if (ph1->index % 2 != 0)
		usleep(200);
	while (1)
	{
		if (rotine1(ph1) == 0 || rotine2(ph1) == 0)
			return (NULL);
		ph1->tmp2 = time_worck();
		ft_print("is sleeping", (time_worck() - ph1->ph->time), ph1);
		while ((time_worck() - ph1->tmp2 < (unsigned long)ph1->ph->time_sleep))
		{
			pthread_mutex_lock((&ph1->ph->var));
			if (ph1->ph->d == 0)
			{
				pthread_mutex_unlock((&ph1->ph->var));
				return (NULL);
			}
			pthread_mutex_unlock((&ph1->ph->var));
			usleep(200);
		}
	}
	return (NULL);
}

void	creat_threads(t_philosopher *ph, t_philo *phh)
{
	int				i;
	unsigned long	x;

	mutex_init(phh, ph);
	i = 0;
	x = time_worck();
	while (i < phh->nmber_philo)
	{
		ph[i].index = i;
		ph[i].ph = phh;
		ph[i].tmp = time_worck();
		ph[i].ph->time = x;
		i++;
	}
	i = 0;
	while (i < phh->nmber_philo)
	{
		pthread_create(&ph[i].t, NULL, rotine, &ph[i]);
		usleep(10);
		i++;
	}
	if (ft_join_philo(ph) == 0)
		return ;
}

int	main(int argc, char **argv)
{
	t_philo			*ph;
	t_philosopher	*p;

	p = NULL;
	if (argc == 5 || argc == 6)
	{
		ph = malloc(sizeof(t_philo));
		if (check_arg(argv, argc, ph) == 0)
		{
			free(ph);
			return (1);
		}
		ph->argc = argc;
		ph->d = 1;
		ph->mutex = malloc(sizeof(pthread_mutex_t) * ph->nmber_philo);
		p = malloc(sizeof(t_philosopher) * ph->nmber_philo);
		creat_threads(p, ph);
		ft_free(p);
	}
	return (0);
}

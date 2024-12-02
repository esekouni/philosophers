/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esekouni <esekouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 17:37:25 by esekouni          #+#    #+#             */
/*   Updated: 2023/05/13 13:22:49 by esekouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philosophers.h"

int	rotine1(t_philosopher *p)
{
	ft_print("is thinking", (time_worck() - p->ph->time), p);
	pthread_mutex_lock(&p->ph->var);
	if (p->ph->d == 0)
	{
		pthread_mutex_unlock(&p->ph->var);
		return (0);
	}
	pthread_mutex_unlock(&p->ph->var);
	return (1);
}

int	rotine_2_1(t_philosopher *p)
{
	while (time_worck() - p->tmp < (unsigned long)p->ph->time_eat)
	{
		pthread_mutex_lock((&p->ph->var));
		if (p->ph->d == 0)
		{
			pthread_mutex_unlock(&(p->ph->mutex[(p->index + 1)
					% p->ph->nmber_philo]));
			pthread_mutex_unlock(&(p->ph->mutex[p->index]));
			pthread_mutex_unlock((&p->ph->var));
			return (0);
		}
		pthread_mutex_unlock((&p->ph->var));
		usleep(200);
	}
	pthread_mutex_lock(&(p->ph->var1));
	if (p->ph->argc == 6)
		p->ph->numb_eat[p->index]++;
	pthread_mutex_unlock(&(p->ph->var1));
	pthread_mutex_unlock(&(p->ph->mutex[p->index]));
	pthread_mutex_unlock(&(p->ph->mutex[(p->index + 1) % p->ph->nmber_philo]));
	return (1);
}

int	rotine2(t_philosopher *p)
{
	pthread_mutex_lock(&(p->ph->mutex[(p->index + 1) % p->ph->nmber_philo]));
	ft_print("has taken a fork", (time_worck() - p->ph->time), p);
	if (p->ph->nmber_philo == 1)
	{
		pthread_mutex_unlock(&(p->ph->mutex[p->index]));
		return (0);
	}
	pthread_mutex_lock(&(p->ph->mutex[p->index]));
	ft_print("has taken a fork", (time_worck() - p->ph->time), p);
	ft_print("is eating", (time_worck() - p->ph->time), p);
	pthread_mutex_lock(&(p->ph->var2));
	p->tmp = time_worck();
	pthread_mutex_unlock(&(p->ph->var2));
	if (rotine_2_1(p) == 0)
		return (0);
	return (1);
}

void	mutex_init(t_philo *ph, t_philosopher *p)
{
	int	i;

	i = 0;
	while (i < ph->nmber_philo)
	{
		pthread_mutex_init(&ph->mutex[i], NULL);
		i++;
	}
	pthread_mutex_init(&(ph->var), NULL);
	pthread_mutex_init(&(ph->var1), NULL);
	pthread_mutex_init(&(ph->var2), NULL);
	pthread_mutex_init(&(ph->var3), NULL);
	pthread_mutex_init(&(p->mutex_print), NULL);
}

int	ft_join_philo(t_philosopher *p)
{
	int	i;

	i = 0;
	if (check_philo(p) == 0)
	{
		while (i < p->ph->nmber_philo)
		{
			pthread_join(p[i].t, NULL);
			i++;
		}
		return (0);
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esekouni <esekouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 02:18:54 by esekouni          #+#    #+#             */
/*   Updated: 2023/05/12 19:43:22 by esekouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philosophers.h"

long	ft_atoi(char *ch)
{
	int		i;
	int		j;
	long	v;

	i = 0;
	v = 0;
	j = 1;
	while (ch[i] == ' ')
		i++;
	if (ch[i] == '-' || ch[i] == '+')
	{
		if (ch[i] == '-')
			j *= -1;
		i++;
	}
	while (ch[i] >= '0' && ch[i] <= '9')
	{
		v *= 10;
		v += ch[i++] - '0';
	}
	return (j * v);
}

unsigned long	time_worck(void)
{
	unsigned long	time;
	struct timeval	rest;

	gettimeofday(&rest, NULL);
	time = ((rest.tv_sec) * 1000) + ((rest.tv_usec) / 1000);
	return (time);
}

void	ft_print(char *ch, unsigned long time, t_philosopher *p)
{
	pthread_mutex_lock(&p->ph->var);
	if (p->ph->d == 1)
	{
		pthread_mutex_lock(&p->mutex_print);
		printf("%ld %d %s\n", time, p->index + 1, ch);
		pthread_mutex_unlock(&p->mutex_print);
	}
	pthread_mutex_unlock(&p->ph->var);
}

int	check_eat_time(t_philosopher *p)
{
	pthread_mutex_lock(&(p->ph->var1));
	if (p->ph->argc == 6 && check_number_eat_times(p->ph->numb_eat,
			p->ph->nmber_philo, p->ph->numb_times_eat) == 1)
	{
		pthread_mutex_lock(&(p->ph->var));
		p->ph->d = 0;
		pthread_mutex_unlock(&(p->ph->var));
		pthread_mutex_unlock(&(p->ph->var1));
		return (0);
	}
	pthread_mutex_unlock(&(p->ph->var1));
	return (1);
}

int	check_number_eat_times(int *arr, int n, int eat_times)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (arr[i] < eat_times)
			return (0);
		i++;
	}
	return (1);
}

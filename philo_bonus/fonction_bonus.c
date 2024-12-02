/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esekouni <esekouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 16:24:29 by esekouni          #+#    #+#             */
/*   Updated: 2023/05/12 19:09:13 by esekouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

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
	if (ch[i] == '+')
		i++;
	while (ch[i] >= '0' && ch[i] <= '9')
	{
		v *= 10;
		v += ch[i++] - '0';
	}
	return (j * v);
}

int	check_caractere(char *av)
{
	int	i;

	i = 0;
	if (av[0] == '+')
		i++;
	while (av[i] == ' ')
		i++;
	while (av[i] != '\0')
	{
		if (av[i] == ' ')
		{
			while (av[i] != '\0')
			{
				if (av[i] != ' ')
					return (0);
				i++;
			}
			return (1);
		}
		if ((av[i] < '0' || av[i] > '9'))
			return (0);
		i++;
	}
	return (1);
}

unsigned long	time_work(void)
{
	unsigned long	time;
	struct timeval	rest;

	gettimeofday(&rest, NULL);
	time = ((rest.tv_sec) * 1000) + ((rest.tv_usec) / 1000);
	return (time);
}

void	check_eat_number(t_philosopher *p)
{
	int	i;

	i = 0;
	while (i < p->ph->nmber_philo)
	{
		sem_wait(p->ph->eat);
		i++;
	}
	i = 0;
	while (i < p->ph->nmber_philo)
	{
		if ((p->ph->status) != 0)
			break ;
		sem_wait(p->ph->eat);
		i++;
	}
	kill(p[0].id, SIGKILL);
}

void	ft_print(char *ch, unsigned long time, t_philosopher *p)
{
	sem_wait(p->ph->print);
	printf("%ld %d %s\n", time, p->index + 1, ch);
	sem_post(p->ph->print);
}

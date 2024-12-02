/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esekouni <esekouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:55:20 by esekouni          #+#    #+#             */
/*   Updated: 2023/05/13 12:55:07 by esekouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philosophers.h"

int	check_car(char *av)
{
	int	i;

	i = 0;
	if (av[0] == '+')
		i++;
	while (av[i] == ' ')
		i++;
	while (av[i])
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
		if (av[i] < '0' || av[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	check_arg_2(t_philo *ph, char **av)
{
	int	i;

	i = 0;
	ph->numb_times_eat = ft_atoi(av[5]);
	if (ph->numb_times_eat == 0)
	{
		printf("invalid arguments\n");
		return (0);
	}
	ph->numb_eat = malloc(sizeof(int) * ph->nmber_philo);
	i = 0;
	while (i < ph->nmber_philo)
	{
		ph->numb_eat[i] = 0;
		i++;
	}
	return (1);
}

int	check_arg(char **av, int ac, t_philo *ph)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (check_car(av[i]) == 0 || av[i][0] == '-'
			|| ft_atoi(av[i]) == 0 || ft_atoi(av[i]) > INT_MAX)
		{
			printf("invalid arguments\n");
			return (0);
		}
		i++;
	}
	ph->nmber_philo = ft_atoi(av[1]);
	ph->time_die = ft_atoi(av[2]);
	ph->time_eat = ft_atoi(av[3]);
	ph->time_sleep = ft_atoi(av[4]);
	if (ac == 6)
	{
		if (check_arg_2(ph, av) == 0)
			return (0);
	}	
	return (1);
}

void	ft_free(t_philosopher *p)
{
	int	i;

	i = 0;
	while (i < p->ph->nmber_philo)
	{
		pthread_mutex_destroy(&p->ph->mutex[i]);
		i++;
	}
	pthread_mutex_destroy(&p->ph->var);
	pthread_mutex_destroy(&p->ph->var1);
	pthread_mutex_destroy(&p->ph->var2);
	pthread_mutex_destroy(&p->ph->var3);
	if (p->ph->argc == 6)
		free(p->ph->numb_eat);
	free(p->ph->mutex);
	free(p->ph);
	free(p);
}

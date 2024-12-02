/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esekouni <esekouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 19:48:10 by esekouni          #+#    #+#             */
/*   Updated: 2023/05/12 19:46:17 by esekouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	check_arg6(char *av)
{
	if (ft_atoi(av) == 0)
	{
		printf("invalid arguments");
		return (0);
	}
	return (1);
}

int	check_args(char **argv, int argc, t_philo *ph)
{
	int	i;

	i = 1;
	ph->argc = argc;
	while (i < ph->argc)
	{
		if (check_caractere(argv[i]) == 0 || argv[i][0] == '-'
			|| ft_atoi(argv[i]) == 0 || ft_atoi(argv[i]) > INT_MAX)
		{
			printf("invalid arguments");
			return (0);
		}
		i++;
	}
	ph->nmber_philo = ft_atoi(argv[1]);
	ph->time_die = ft_atoi(argv[2]);
	ph->time_eat = ft_atoi(argv[3]);
	ph->time_sleep = ft_atoi(argv[4]);
	if (ph->argc == 6)
	{
		if (check_arg6(argv[5]) == 0)
			return (0);
		ph->numb_times_eat = ft_atoi(argv[5]);
	}
	return (1);
}

void	rotine_2(t_philosopher *p, int *eat)
{
	if (p->ph->argc == 6)
	{
		sem_wait(p->ph->eat_time);
		p->numb_eat++;
		sem_post(p->ph->eat_time);
		if (p->numb_eat >= p->ph->numb_times_eat && (*eat) == 0)
		{
			(*eat) = 1;
			sem_post(p->ph->eat);
		}
	}
}

void	semaphore_init(t_philo *ph)
{
	sem_unlink("/sem");
	sem_unlink("/tmp");
	sem_unlink("/print");
	sem_unlink("/eat_time");
	sem_unlink("/eat");
	ph->sem = sem_open("/sem", O_CREAT, 644, ph->nmber_philo);
	ph->print = sem_open("/print", O_CREAT, 644, 1);
	ph->tmp = sem_open("/tmp", O_CREAT, 644, 1);
	ph->eat_time = sem_open("/eat_time", O_CREAT, 644, 1);
	ph->eat = sem_open("/eat", O_CREAT, 644, ph->nmber_philo);
	if (ph->sem == SEM_FAILED || ph->print == SEM_FAILED
		|| ph->tmp == SEM_FAILED || ph->eat == SEM_FAILED
		|| ph->eat_time == SEM_FAILED)
	{
		printf("ERROR\n");
		exit(0);
	}
}

void	creation_process(t_philosopher *p)
{
	int		i;
	pid_t	pid;

	i = -1;
	while ((++i) < p->ph->nmber_philo)
	{
		pid = fork();
		if (pid == -1)
		{
			i = -1;
			while ((++i) < p->ph->nmber_philo)
			{
				if (p[i].id != -1)
					kill(p[i].id, SIGKILL);
			}
		}
		else if (pid == 0)
		{
			pthread_create(&(p[i].t), NULL, th_rotine, &p[i]);
			rotine(&p[i]);
			exit(1);
		}
		else
			p[i].id = pid;
	}
}

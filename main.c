/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 10:38:22 by jdidier           #+#    #+#             */
/*   Updated: 2022/01/07 19:48:20 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

t_datas	set_datas(int argc, char **argv)
{
	t_datas	datas;

	datas.nbr_of_philo = ft_atoi(argv[1]);
	datas.time_to_die = ft_atoi(argv[2]);
	datas.time_to_eat = ft_atoi(argv[3]);
	datas.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		datas.nbr_of_meal = ft_atoi(argv[5]);
	else
		datas.nbr_of_meal = -1;
	datas.forks = malloc(sizeof(pthread_mutex_t) * datas.nbr_of_philo);
	return (datas);
}

t_philo	new_philo(int id, t_datas *datas)
{
	t_philo	philo;

	philo.id = id;
	philo.datas = datas;
	philo.is_eating = 0;
	philo.last_meal = 0;
	if (philo.id % 2 == 0)
	{
		philo.fork1 = philo.id;
		philo.fork2 = (philo.id + 1) % philo.datas->nbr_of_philo;
	}
	else
	{
		philo.fork1 = (philo.id + 1) % philo.datas->nbr_of_philo;
		philo.fork2 = philo.id;
	}
	return (philo);
}

t_philo	*set_philos(t_datas *datas)
{
	t_philo	*philos;
	int	i;

	i = 0;
	philos = malloc(sizeof(t_philo) * datas->nbr_of_philo);
	while (i < datas->nbr_of_philo)
	{
		philos[i] = new_philo(i, datas);
		i++;
	}
	return (philos);
}

void	print_action(t_philo *philo, long time, char *str)
{
	pthread_mutex_lock(&philo->datas->print);
	printf("%ld\t%d %s\n", time, philo->id + 1, str);
	pthread_mutex_unlock(&philo->datas->print);
}

void	*thread_function(void *varg)
{
	t_philo	*philo;
	int		is_dead;
	long	timer;


	is_dead = 1;
	philo = (t_philo *)varg;
	//printf("start of thread_function of id: %d\n", philo->id);
	philo->last_meal = get_timestamp(0);
	while (is_dead)
	{
		timer = get_timestamp(0);
		pthread_mutex_lock(&philo->datas->forks[philo->fork1]);
		print_action(philo, get_timestamp(timer), FORK);
		pthread_mutex_lock(&philo->datas->forks[philo->fork2]);
		print_action(philo, get_timestamp(timer), FORK);
		philo->is_eating = 1;
		print_action(philo, get_timestamp(timer), EAT);
		ft_usleep(philo->datas->time_to_eat);
		pthread_mutex_unlock(&philo->datas->forks[philo->fork1]);
		pthread_mutex_unlock(&philo->datas->forks[philo->fork2]);
		philo->last_meal = get_timestamp(0);
		philo->is_eating = 0;
		print_action(philo, get_timestamp(timer), EAT);
		ft_usleep(philo->datas->time_to_sleep);
		print_action(philo, get_timestamp(timer), THINK);
	}
	//printf("end of thread_function of id: %d\n", philo->id);
	return (NULL);
}

void	run(t_datas *datas, t_philo *p)
{
	int	i;
	
	i = 0;
	while (i < datas->nbr_of_philo)
		pthread_mutex_init(datas->forks + i++, NULL);
	pthread_mutex_init(&datas->print, NULL);
	i = 0;
	while (i < datas->nbr_of_philo)
	{
		pthread_create(&((p + i)->philo), NULL, thread_function, (p + i));
		i++;
	}
	i = 0;
	while (i < datas->nbr_of_philo)
		pthread_join((p + i++)->philo, NULL);
	i = 0;
	while (i < datas->nbr_of_philo)
		pthread_mutex_destroy(datas->forks + i++);
	pthread_mutex_destroy(&datas->print);
}

/*
void	*check_death(void *varg)
{
	t_philo	*philos;
	t_datas	*datas;
	int		i;

	philos = (t_philo *)varg;
	datas = philos->datas;
	i = 0;
	while (i < datas->nbr_of_philo)
	{
		if(!(philos + i)->is_eating)
		{
			//if 
		}
		i++;
	}
	
	if (last_meal > 0)
	{
		if (get_timestamp(last_meal) > philo->datas->time_to_die)
		{
			printf("%ld %d die\n", get_timestamp(timer), philo->id + 1);
			break;
		}	
	}
	
}
*/

int	main(int argc, char **argv)
{
	t_datas		datas;
	t_philo		*philos;
	//pthread_t	death_checker;

	if (argc > 4 && argc < 7)
	{
		if (check(argc, argv))
		{
			datas = set_datas(argc, argv);
			// DEBUG:
			printf("number of philos: %d\n", datas.nbr_of_philo);
			printf("time to die: %d\n", datas.time_to_die);
			printf("time to eat: %d\n", datas.time_to_eat);
			printf("time to sleep: %d\n", datas.time_to_sleep);
			printf("number of meal: %d\n", datas.nbr_of_meal);
			// TODO: Run philosopher process with datas as paramater
			philos = set_philos(&datas);
			run(&datas, philos);
			//pthread_create(&death_checker, NULL, check_death, philos);
			//pthread_join(death_checker, NULL);
			free(philos);
			free(datas.forks);
		}
		else
			printf("ERROR. Program's arguments should be digit characters\n");
	}
	else
		printf("ERROR. Program takes 4 or 5 arguments.\n");
	return (0);
}

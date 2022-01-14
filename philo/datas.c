/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   datas.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 16:07:56 by jdidier           #+#    #+#             */
/*   Updated: 2022/01/14 15:42:22 by jdidier          ###   ########.fr       */
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
	datas.start_time = get_timestamp(0);
	datas.game_over = 0;
	return (datas);
}

t_philo	new_philo(int id, t_datas *datas)
{
	t_philo	philo;

	philo.id = id;
	philo.datas = datas;
	philo.last_meal = 0;
	philo.meal_counter = datas->nbr_of_meal;
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
	int		i;

	i = 0;
	philos = malloc(sizeof(t_philo) * datas->nbr_of_philo);
	if (!philos)
		return (NULL);
	while (i < datas->nbr_of_philo)
	{
		philos[i] = new_philo(i, datas);
		i++;
	}
	return (philos);
}

void	init_mutex(t_datas *datas)
{
	int	i;

	i = 0;
	while (i < datas->nbr_of_philo)
		pthread_mutex_init(datas->forks + i++, NULL);
	pthread_mutex_init(&datas->mutex, NULL);
}

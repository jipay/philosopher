/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 10:38:22 by jdidier           #+#    #+#             */
/*   Updated: 2022/01/16 22:00:41 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	print_action(t_philo *philo, long time, char *str)
{
	if (!get_game_over(philo->datas))
	{
		pthread_mutex_lock(&philo->datas->mutex);
		printf("%ld\t%d %s\n", time, philo->id + 1, str);
		pthread_mutex_unlock(&philo->datas->mutex);
	}
}

void	launcher(t_datas *datas, t_philo *philos)
{
	if (datas->nbr_of_philo == 1)
	{
		printf("%ld\t%d %s\n", get_timestamp(datas->start_time), 1, FORK);
		usleep(datas->time_to_die * 1000);
		printf("%ld\t%d %s\n", get_timestamp(datas->start_time), 1, DIE);
	}
	else
		run(datas, philos);
	free(philos);
	free(datas->forks);
}

int	main(int argc, char **argv)
{
	t_datas		datas;
	t_philo		*philos;

	if (argc > 4 && argc < 7)
	{
		if (check(argc, argv))
		{
			datas = set_datas(argc, argv);
			if (datas.nbr_of_meal == 0)
				return (0);
			datas.forks = malloc(sizeof(pthread_mutex_t) * datas.nbr_of_philo);
			if (!datas.forks)
				return (1);
			philos = set_philos(&datas);
			if (!philos)
				return (1);
			launcher(&datas, philos);
		}
		else
			printf("ERROR. Args should be positive digit characters\n");
	}
	else
		printf("ERROR. Program takes 4 or 5 arguments.\n");
	return (0);
}

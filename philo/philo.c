/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 16:10:36 by jdidier           #+#    #+#             */
/*   Updated: 2022/01/16 22:07:18 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	has_all_eat_their_meal(t_datas *datas, t_philo *p)
{
	int	i;

	i = 0;
	while (i < datas->nbr_of_philo)
	{
		if (get_meal_counter(p + i) > 0)
			return (0);
		i++;
	}
	return (1);
}

void	death_watcher(t_datas *datas, t_philo *p)
{
	int		i;

	i = 0;
	if (datas->nbr_of_meal != -1 && has_all_eat_their_meal(datas, p))
	{
		set_game_over(datas, 1);
		return ;
	}
	while (i < datas->nbr_of_philo)
	{
		if (get_game_over(datas))
			return ;
		if (get_last_meal(p + i) + datas->time_to_die
			<= get_timestamp(datas->start_time))
		{
			pthread_mutex_lock(&datas->mutex);
			datas->game_over = 1;
			printf("%ld\t%d %s\n", get_timestamp(datas->start_time),
				(p + i)->id + 1, DIE);
			pthread_mutex_unlock(&datas->mutex);
			return ;
		}
		i++;
	}
}

void	*thread_function(void *varg)
{
	t_philo	*philo;

	philo = (t_philo *)varg;
	while (!get_game_over(philo->datas))
	{
		pthread_mutex_lock(&philo->datas->forks[philo->fork1]);
		print_action(philo, get_timestamp(philo->datas->start_time), FORK);
		pthread_mutex_lock(&philo->datas->forks[philo->fork2]);
		print_action(philo, get_timestamp(philo->datas->start_time), FORK);
		set_last_meal(philo, get_timestamp(philo->datas->start_time));
		print_action(philo, get_timestamp(philo->datas->start_time), EAT);
		ft_usleep(philo->datas->time_to_eat, philo->datas);
		pthread_mutex_unlock(&philo->datas->forks[philo->fork1]);
		pthread_mutex_unlock(&philo->datas->forks[philo->fork2]);
		if (philo->meal_counter == 0)
			return (NULL);
		print_action(philo, get_timestamp(philo->datas->start_time), SLEEP);
		ft_usleep(philo->datas->time_to_sleep, philo->datas);
		print_action(philo, get_timestamp(philo->datas->start_time), THINK);
	}
	return (NULL);
}

void	run(t_datas *datas, t_philo *p)
{
	int	i;

	init_mutex(datas);
	i = 0;
	while (i < datas->nbr_of_philo)
	{
		pthread_create(&((p + i)->philo), NULL, thread_function, (p + i));
		i += 2;
		if (i >= datas->nbr_of_philo && i % 2 == 0)
			i = 1;
		usleep(1000);
	}
	while (!get_game_over(datas))
		death_watcher(datas, p);
	i = 0;
	while (i < datas->nbr_of_philo)
		pthread_join((p + i++)->philo, NULL);
	i = 0;
	while (i < datas->nbr_of_philo)
		pthread_mutex_destroy(datas->forks + i++);
	pthread_mutex_destroy(&datas->mutex);
}

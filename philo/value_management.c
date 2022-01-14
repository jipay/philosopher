/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 16:03:35 by jdidier           #+#    #+#             */
/*   Updated: 2022/01/14 15:38:44 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	get_game_over(t_datas *datas)
{
	int	game_over;

	pthread_mutex_lock(&datas->mutex);
	game_over = datas->game_over;
	pthread_mutex_unlock(&datas->mutex);
	return (game_over);
}

void	set_game_over(t_datas *datas, int game_over)
{
	pthread_mutex_lock(&datas->mutex);
	datas->game_over = game_over;
	pthread_mutex_unlock(&datas->mutex);
}

long	get_last_meal(t_philo *philo)
{
	long	last_meal;

	pthread_mutex_lock(&philo->datas->mutex);
	last_meal = philo->last_meal;
	pthread_mutex_unlock(&philo->datas->mutex);
	return (last_meal);
}

void	set_last_meal(t_philo *philo, long last_meal)
{
	pthread_mutex_lock(&philo->datas->mutex);
	philo->last_meal = last_meal;
	if (philo->datas->nbr_of_meal != -1)
		philo->meal_counter--;
	pthread_mutex_unlock(&philo->datas->mutex);
}

int	get_meal_counter(t_philo *philo)
{
	int	meal_counter;

	pthread_mutex_lock(&philo->datas->mutex);
	meal_counter = philo->meal_counter;
	pthread_mutex_unlock(&philo->datas->mutex);
	return (meal_counter);
}

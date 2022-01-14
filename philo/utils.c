/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 10:50:29 by jdidier           #+#    #+#             */
/*   Updated: 2022/01/14 15:41:59 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	check(int argc, char **argv)
{
	int		i;

	i = 1;
	while (i < argc)
	{
		if (!check_arg(argv[i]))
			return (0);
		if (!check_int(argv[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_arg(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	check_int(char *str)
{
	int			minus;
	long int	result;

	minus = 1;
	result = 0;
	if (*str == '-')
	{
		minus *= -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		result = result * 10 + (*str - 48);
		str++;
	}
	result *= minus;
	if (result >= INT_MIN && result <= INT_MAX)
		return (1);
	else
		return (0);
}

long	get_timestamp(long start_ts)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (((tv.tv_sec * 1000) + tv.tv_usec / 1000) - start_ts);
}

void	ft_usleep(int duration, t_datas *datas)
{
	long	start;
	long	current;

	start = get_timestamp(0);
	current = start;
	if (get_game_over(datas))
		return ;
	while (duration > current - start)
	{
		usleep(100);
		current = get_timestamp(0);
	}
}

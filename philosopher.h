/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 10:38:46 by jdidier           #+#    #+#             */
/*   Updated: 2022/01/07 19:43:20 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

# define FORK	"has taken a fork"
# define EAT	"is eating"
# define THINK	"is thinking"
# define SLEEP	"is sleeping"
# define DIE	"die"
# define INT_MAX	2147483647
# define INT_MIN	-2147483648

typedef struct	s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

typedef struct	s_datas
{
	int				nbr_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_of_meal;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
}				t_datas;

typedef struct s_philo
{
	int				fork1;
	int				fork2;
	int				is_eating;
	unsigned int	id;
	long			last_meal;
	pthread_t		philo;
	t_datas			*datas;
}				t_philo;

int	check(int argc, char **argv);
int	check_arg(char *str);
int	check_int(char *str);

int	ft_isdigit(int c);
int	ft_strcmp(char *s1, char *s2);
int	ft_atoi(const char *nptr);

long	get_timestamp(long start_ts);
void	ft_usleep(int duration);
#endif
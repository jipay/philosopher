/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 11:15:25 by jdidier           #+#    #+#             */
/*   Updated: 2022/01/03 11:20:56 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] == s2[i])
			i++;
		else
			return (s1[i] - s2[i]);
	}
	return (s1[i] - s2[i]);
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *nptr)
{
	int	minus;
	int	result;

	minus = 1;
	result = 0;
	if (!(ft_isdigit(*nptr) || *nptr == '-' || *nptr == '+'
			|| ft_isspace(*nptr)))
		return (0);
	else
	{
		while (ft_isspace(*nptr))
			nptr++;
		if (*nptr == '-' || *nptr == '+')
		{
			if (*nptr == '-')
				minus *= -1;
			nptr++;
		}
	}
	while (ft_isdigit(*nptr))
	{
		result = result * 10 + (*nptr - 48);
		nptr++;
	}
	return (result * minus);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltulune <ltulune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 09:34:49 by ltulune           #+#    #+#             */
/*   Updated: 2021/06/04 11:54:55 by ltulune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char b)
{
	if (b == ' ' || b == '\t' || b == '\n' || b == '\v' || b == '\f'
		|| b == '\r')
		return (1);
	return (0);
}

static int	put_sign(long int b, int s)
{
	if (s == -1)
	{
		if (b > 2147483648)
			return (0);
		else
			return (s * b);
	}
	if (b > 2147483647)
		return (-1);
	return (b);
}

int	ft_atoi(const char *nptr)
{
	long int	buf;
	int			sign;

	buf = 0;
	sign = 1;
	while (*nptr)
	{
		if (ft_isspace(*nptr))
			;
		else if (*nptr == '+' && ft_isdigit(*(nptr + 1)))
			sign = 1;
		else if (*nptr == '-' && ft_isdigit(*(nptr + 1)))
			sign = -1;
		else if (!(ft_isdigit(*nptr)))
			return (0);
		else if (ft_isdigit(*nptr))
			buf = buf * 10 + *nptr - '0';
		if (buf > 2147483648
			|| (ft_isdigit(*nptr) && !(ft_isdigit(*(nptr + 1)))))
			return (put_sign(buf, sign));
		nptr++;
	}
	return (put_sign(buf, sign));
}

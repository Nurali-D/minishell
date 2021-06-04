/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltulune <ltulune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 09:35:55 by ltulune           #+#    #+#             */
/*   Updated: 2021/06/04 15:05:49 by ltulune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen(int num)
{
	int			i;

	i = 0;
	while (num)
	{
		num /= 10;
		i++;
	}
	return (i);
}

void	ft_wrnum2(char *b, long int c, int i)
{
	b[i] = '\0';
	while (c)
	{
		b[i - 1] = c % 10 + '0';
		c /= 10;
		i--;
	}
}

static char	*ft_wrnum(char *b, long int c)
{
	int	i;
	int	j;

	i = ft_intlen(c);
	j = i;
	if (c < 0 && i > 0)
	{
		b[0] = '-';
		c *= -1;
		b[i + 1] = '\0';
		while (c)
		{
			b[i] = c % 10 + '0';
			c /= 10;
			i--;
		}
	}
	else if (j > 0)
		ft_wrnum2(b, c, j);
	return (b);
}

char	*ft_itoa(int n)
{
	char		*ret;
	long int	nl;

	ret = (char *)malloc((ft_intlen(n) + 2) * sizeof(char));
	if (!(ret))
		return (NULL);
	nl = n;
	if (n == 0)
	{
		ret[0] = '0';
		ret[1] = '\0';
		return (ret);
	}
	return (ft_wrnum(ret, nl));
}

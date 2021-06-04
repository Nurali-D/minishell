/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltulune <ltulune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 09:36:35 by ltulune           #+#    #+#             */
/*   Updated: 2021/06/04 12:16:34 by ltulune          ###   ########.fr       */
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

static long int	ft_pow10(int i)
{
	long int	buf;

	buf = 1;
	i -= 1;
	while (i)
	{
		buf *= 10;
		i--;
	}
	return (buf);
}

void	ft_putnbr_fd(int n, int fd)
{
	char		s;
	int			i;
	long int	num;

	if (n == 0)
	{
		ft_putchar_fd('0', fd);
		return ;
	}
	i = ft_intlen(n);
	num = n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		num = -1 * num;
	}
	while (i)
	{
		s = (int)(num / ft_pow10(i)) + '0';
		num = num % ft_pow10(i);
		ft_putchar_fd(s, fd);
		i--;
	}
}

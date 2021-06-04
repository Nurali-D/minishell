/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltulune <ltulune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 16:08:24 by ltulune           #+#    #+#             */
/*   Updated: 2021/06/04 12:14:20 by ltulune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*buf;

	if (!s && !c && !n)
		return (NULL);
	buf = (unsigned char *)s;
	while (n)
	{
		if (*buf == (unsigned char)c)
			return (buf);
		n--;
		buf++;
	}
	return (NULL);
}

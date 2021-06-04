/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltulune <ltulune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 15:51:36 by ltulune           #+#    #+#             */
/*   Updated: 2021/06/04 12:15:27 by ltulune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*buf;

	if (!b && !c && !len)
		return (NULL);
	buf = (unsigned char *)b;
	while (len)
	{
		*buf = (unsigned char)c;
		buf++;
		len--;
	}
	return (b);
}

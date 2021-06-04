/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltulune <ltulune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 15:59:38 by ltulune           #+#    #+#             */
/*   Updated: 2021/06/04 12:15:00 by ltulune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*buf_dest;
	unsigned char	*buf_src;

	if (!dst && !src)
		return (NULL);
	buf_dest = (unsigned char *)dst;
	buf_src = (unsigned char *)src;
	while (n)
	{
		*buf_dest = *buf_src;
		n--;
		buf_dest++;
		buf_src++;
	}
	return (dst);
}

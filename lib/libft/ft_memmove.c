/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltulune <ltulune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 20:22:13 by ltulune           #+#    #+#             */
/*   Updated: 2021/06/04 12:15:14 by ltulune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*buf_dst;
	unsigned char	*buf_src;

	if ((!dst && !src && !len) || (!dst && !src))
		return (NULL);
	buf_dst = (unsigned char *)dst;
	buf_src = (unsigned char *)src;
	while (len)
	{
		if (buf_dst > buf_src)
			buf_dst[len - 1] = buf_src[len - 1];
		else
		{
			*buf_dst = *buf_src;
			buf_dst++;
			buf_src++;
		}
		len--;
	}
	return (dst);
}

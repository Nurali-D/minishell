/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltulune <ltulune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 18:51:30 by ltulune           #+#    #+#             */
/*   Updated: 2021/06/04 12:13:44 by ltulune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*buf_dst;
	unsigned char	*buf_src;

	if ((dst == NULL && src == NULL))
		return (NULL);
	buf_dst = (unsigned char *)dst;
	buf_src = (unsigned char *)src;
	while (n)
	{
		if (*buf_src != (unsigned char)c)
		{
			*buf_dst = *buf_src;
			buf_dst++;
			buf_src++;
			n--;
		}
		else
		{
			*buf_dst = *buf_src;
			return (buf_dst + 1);
		}
	}
	return (NULL);
}

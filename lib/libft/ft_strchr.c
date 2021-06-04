/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltulune <ltulune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 18:47:23 by ltulune           #+#    #+#             */
/*   Updated: 2021/06/04 12:46:00 by ltulune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*buf;

	buf = (char *)s;
	while (*buf)
	{
		if (*buf == (unsigned char)c)
			return (buf);
		else
			buf++;
	}
	if (*buf == '\0' && (unsigned char)c == '\0')
		return (buf);
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltulune <ltulune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 18:47:50 by ltulune           #+#    #+#             */
/*   Updated: 2021/06/04 12:48:46 by ltulune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*buf;

	buf = NULL;
	while (*s)
	{
		if (*s == (char)c)
			buf = (char *)s;
		s++;
	}
	if (buf)
		return (buf);
	if (*s == '\0' && (char)c == '\0')
	{
		buf = (char *)s;
		return (buf);
	}
	return (NULL);
}

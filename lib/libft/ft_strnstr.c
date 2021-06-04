/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltulune <ltulune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 23:56:31 by ltulune           #+#    #+#             */
/*   Updated: 2021/06/04 12:48:25 by ltulune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hsk, const char *ndl, size_t len)
{
	size_t	i;
	size_t	j;

	if (*ndl == '\0')
		return ((char *)hsk);
	j = 0;
	while (hsk[j] != '\0' && j < len)
	{
		if (hsk[j] == ndl[0])
		{
			i = 1;
			while (ndl[i] != '\0' && hsk[j + i] == ndl[i]
				&& (j + i) < len)
				i++;
			if (ndl[i] == '\0')
				return ((char *)&hsk[j]);
		}
		j++;
	}
	return (NULL);
}

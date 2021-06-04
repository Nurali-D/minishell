/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltulune <ltulune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 09:38:07 by ltulune           #+#    #+#             */
/*   Updated: 2021/06/04 12:50:27 by ltulune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*subs;
	size_t	i;

	if (!s)
		return (NULL);
	if ((size_t)start >= ft_strlen(s))
	{
		subs = (char *)malloc(sizeof(char));
		if (!(subs))
			return (NULL);
		subs[0] = '\0';
		return (subs);
	}
	subs = (char *)malloc((len + 1) * sizeof(char));
	if (!(subs))
		return (NULL);
	i = 0;
	while (s[start] && i < len)
	{
		subs[i] = s[start];
		i++;
		start++;
	}
	subs[i] = '\0';
	return (subs);
}

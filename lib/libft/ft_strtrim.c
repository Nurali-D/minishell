/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltulune <ltulune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 09:37:59 by ltulune           #+#    #+#             */
/*   Updated: 2021/06/04 12:49:15 by ltulune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	find_begin(char const *s, char const *st)
{
	size_t		i;
	size_t		j;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (st[j])
		{
			if (s[i] == st[j])
				break ;
			if (j == ft_strlen(st) - 1)
				return (i);
			j++;
		}
		i++;
	}
	if (st[0] == '\0')
		return (0);
	return (ft_strlen(s));
}

static size_t	find_end(char const *s, char const *st)
{
	size_t		i;
	size_t		j;

	i = ft_strlen(s) - 1;
	while (i != (size_t)0 - 1)
	{
		j = ft_strlen(st) - 1;
		while (j != (size_t)0 - 1)
		{
			if (s[i] == st[j])
				break ;
			if (j == 0)
				return (i);
			j--;
		}
		i--;
	}
	return (ft_strlen(s));
}

static void	ft_copy(char const *s, char *rt, size_t b, size_t e)
{
	size_t		i;

	i = 0;
	while (b <= e)
	{
		rt[i] = s[b];
		i++;
		b++;
	}
	rt[i] = '\0';
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		begin;
	size_t		end;
	char		*ret;

	if (!s1 || !set)
		return (NULL);
	if (s1[0] == '\0')
	{
		ret = (char *)malloc(sizeof(char));
		if (ret == NULL)
			return (NULL);
		ret[0] = '\0';
		return (ret);
	}
	begin = find_begin(s1, set);
	end = find_end(s1, set);
	ret = (char *)malloc((end - begin + 2) * sizeof(char));
	if (ret == NULL)
		return (NULL);
	ft_copy(s1, ret, begin, end);
	return (ret);
}

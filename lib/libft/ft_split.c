/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltulune <ltulune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 09:36:52 by ltulune           #+#    #+#             */
/*   Updated: 2021/06/04 12:44:50 by ltulune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nw(char const *str, char d)
{
	size_t	i;
	int		n;

	i = 0;
	n = 0;
	while (str[i])
	{
		while (str[i] == d)
			i++;
		if (str[i] != '\0')
			n++;
		while (str[i] && str[i] != d)
			i++;
	}
	return (n);
}

static char	*ft_strdups(const char *s1, char c1, size_t n)
{
	char	*dup;
	size_t	i;

	dup = (char *)malloc((n + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	i = 0;
	while (s1[i] != c1 && s1[i] != '\0')
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

static char	**ft_free(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char		**res;
	t_counters	cnt;

	cnt.i = 0;
	cnt.k = 0;
	res = (char **)malloc((ft_nw(s, c) + 1) * sizeof(char *));
	if (!s || !(res))
		return (NULL);
	while (s[cnt.i])
	{
		while (s[cnt.i] == c)
			cnt.i++;
		cnt.j = cnt.i;
		while (s[cnt.i] != c && s[cnt.i] != '\0')
			cnt.i++;
		if (cnt.i > cnt.j)
		{
			res[cnt.k] = ft_strdups(&s[cnt.j], c, cnt.i - cnt.j);
			if (!(res))
				return (ft_free(res));
			cnt.k++;
		}
	}
	res[cnt.k] = NULL;
	return (res);
}

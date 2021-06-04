#include "get_next_line.h"

size_t				ft_strlen(const char *s)
{
	size_t			n;

	n = 0;
	while (*s)
	{
		n++;
		s++;
	}
	return (n);
}

void				*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*buf_dest;
	unsigned char	*buf_src;

	if (!dst && !src)
		return (NULL);
	buf_dest = dst;
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

char				*ft_strjoin_mod(char *s1, char const *s2)
{
	char			*res;
	int				flag;

	flag = 0;
	if (!s1)
	{
		if (!(s1 = (char*)malloc(sizeof(char))))
			return (NULL);
		s1[0] = '\0';
		flag = 1;
	}
	if (!s2)
		return (NULL);
	res = (char*)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	ft_memcpy(res, s1, ft_strlen(s1));
	ft_memcpy(&res[ft_strlen(s1)], s2, ft_strlen(s2));
	res[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	if (flag == 1)
		free(s1);
	return (res);
}

char				*ft_strdup(const char *s1)
{
	char			*dup;
	size_t			i;

	dup = malloc(ft_strlen(s1) + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char				*ft_strchr(const char *s, int c)
{
	char			*buf;

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

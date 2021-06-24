#include "minishell.h"

static int	is_key(char c)
{
	if (c == '_' || ft_isalnum(c))
		return (1);
	return (0);
}

char	*is_key_in_env(char *key, t_env *env)
{
	t_env *tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}
char	*ft_strjoin2(char const *s1, char const *s2)
{
	char	*res;

	if (!s1 || !s2)
		return (NULL);
	res = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	ft_memcpy(res, s1, ft_strlen(s1));
	ft_memcpy(&res[ft_strlen(s1)], s2, ft_strlen(s2));
	res[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	return (res);
}
char	*replace_key(char *str, char *value, int *i, int j)
{
	char	*before;
	char	*after;
	char	*tmp;
	// char	*tmp2;

	before = ft_substr(str, 0, j);
	after = ft_strdup(str + *i);
	if (before[0] != '\0')
		tmp = ft_strjoin2(before, value);
	*i = ft_strlen(tmp);
	// tmp2 = tmp;
	if (after[0] != '\0')
		tmp = ft_strjoin2(tmp, after);
	// free(str);
	// free(value);
	// free(before);
	// free(after);
	// free(tmp2);
	return (tmp);
}

char	*treat_dollar(char *str, int *i, t_env *env)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	j = *i;
	while (str[++*i])
		if (!is_key(str[*i]))
			break;
	if (*i == j + 1)
		return (str);
	tmp = ft_substr(str, j + 1, *i - j - 1);
	tmp2 = is_key_in_env(tmp, env);
	if (tmp2 != NULL)
		str = replace_key(str, tmp2, i, j);
	return (str);
}

#include "minishell.h"

char	*triplejoin(char *s1, char *s2, char *s3)
{
	char	*res;

	if (!s1 || !s2)
		return (NULL);
	res = (char *)malloc((ft_strlen(s1) + ft_strlen(s2)
				+ ft_strlen(s3) + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	ft_memcpy(res, s1, ft_strlen(s1));
	ft_memcpy(&res[ft_strlen(s1)], s2, ft_strlen(s2));
	ft_memcpy(&res[ft_strlen(s1) + ft_strlen(s2)], s3, ft_strlen(s3));
	res[ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3)] = '\0';
	return (res);
}

char	**get_env_arr(t_env *env)
{
	int		i;
	char	**res;
	t_env	*tmp;

	tmp = env;
	i = ft_lstsize(tmp);
	res = (char **)malloc(sizeof(char *) * i);
	i = -1;
	while (tmp)
	{
		res[++i] = triplejoin(tmp->key, "=", tmp->value);
		tmp = tmp->next;
	}
	res[i + 1] = NULL;
	return (res);
}

t_env	*ft_getenv(t_env *head, char *env)
{
	t_env	*tmp;

	tmp = head;
	while (tmp)
	{
		if ((ft_strcmp(tmp->key, env)) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int	ft_arrlen(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_isenv(int c)
{
	if (ft_isalpha(c) || c == '_')
		return (0);
	else
		return (1);
}

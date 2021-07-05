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

char	**get_env_arr(t_msh *ms)
{
	int		i;
	char	**res;
	t_env	*tmp;

	tmp = ms->env_list;
	i = ft_lstsize(tmp);
	res = (char **)ft_calloc(i, sizeof(char *));
	if (res == NULL)
		return (NULL);
	i = -1;
	while (tmp)
	{
		res[++i] = triplejoin(tmp->key, "=", tmp->value);
		if (res[i] == NULL)
			return (NULL);
		tmp = tmp->next;
	}
	res[i + 1] = NULL;
	return (res);
}

t_env	*ft_getcwd(t_env *head, char *env)
{
	t_env	*tmp;

	tmp = head;
	while ((ft_strcmp(tmp->key, env)) != 0)
		tmp = tmp->next;
	return (tmp);
}

#include "minishell.h"

int	ft_lstsize(t_env *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

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

int	get_env_arr(t_msh *ms)
{
	int		i;
	t_env	*tmp;

	tmp = ms->env_list;
	i = ft_lstsize(tmp);
	ms->env = (char **)ft_calloc(i, sizeof(char *));
	if (ms->env == NULL)
		return (1);
	i = -1;
	while (tmp)
	{
		ms->env[++i] = triplejoin(tmp->key, "=", tmp->value);
		if (ms->env[i] == NULL)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}


t_env	*ft_getcwd(t_env *head, char *env)
{
	t_env	*tmp;

	tmp = head;
	while ((ft_strcmp(tmp->key, env)) != 0)
		tmp = tmp->next;
	return (tmp);
}

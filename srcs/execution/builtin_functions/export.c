#include "minishell.h"

char	**lsttoarr(t_env *lst)
{
	int		i;
	char	**res;
	char	*ptr;
	t_env	*tmp;

	tmp = lst;
	i = ft_lstsize(tmp);
	res = (char **)malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (tmp)
	{
		i++;
		if (tmp->value != NULL)
		{
			ptr = triplejoin("\"", tmp->value, "\"");
			res[i] = triplejoin(tmp->key, "=", ptr);
			free(ptr);
		}
		else
			res[i] = ft_strdup(tmp->key);
		tmp = tmp->next;
	}
	res[i + 1] = NULL;
	return (res);
}

void	print_export(t_env *export)
{
	int		i;
	char	**tmp;

	tmp = lsttoarr(export);
	bubblesort(tmp);
	i = -1;
	while (tmp && tmp[++i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(tmp[i], 1);
		ft_putstr_fd("\n", 1);
	}
	i = -1;
	while (tmp && tmp[++i])
		free(tmp[i]);
	free(tmp);
}

void	add_export(t_env *lst, char **args, int i, int len)
{
	char	*name;
	char	*value;
	t_env	*temp;

	temp = lst;
	len = ft_strlen(args[i]) - ft_strlen(ft_strchr(args[i], '='));
	name = ft_substr(args[i], 0, len);
	if (ft_isenv(name))
	{
		env_error("export: ", name, "not a valid identifier", 1);
		free(name);
		return ;
	}
	value = NULL;
	if ((ft_strchr(args[i], '=')) != NULL)
		value = ft_strdup(&args[i][len + 1]);
	temp = ft_getenv(lst, name);
	if (temp)
	{
		if (value != NULL)
			temp->value = value;
	}
	else
		ft_lstadd_back(lst, ft_lstnew(name, value));
}

void	export_execution(t_env *lst, char **args)
{
	int	i;

	g_status = 0;
	if (!args[1])
		print_export(lst);
	else
	{
		i = 0;
		while (args[++i])
			add_export(lst, args, i, 0);
	}
}

#include "minishell.h"

char **lsttoarr(t_env *lst)
{
	int		i;
	char	**res;
	t_env	*tmp;

	tmp = lst;
	i = ft_lstsize(tmp);
	res = (char **)ft_calloc(i, sizeof(char *));
	if (res == NULL)
		return (NULL);
	i = -1;
	while (tmp)
	{
		i++;
		if (tmp->value != NULL)
			res[i] = triplejoin(tmp->key, "=", triplejoin("\"", tmp->value, "\""));
		else
			res[i] = ft_strdup(tmp->key);
		tmp = tmp->next;
	}
	res[i + 1] = NULL;
	return (res);
}

void	print_export(t_env *export)
{
	char	**tmp;

	tmp = lsttoarr(export);
	bubblesort(tmp);
	while (tmp && *tmp)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(*tmp, 1);
		ft_putstr_fd("\n", 1);
		tmp++;
	}
}

void	export_execution(t_env *lst, char **args)
{
	int		i;
	int		len;
	char	*res1;
	char	*res2;
	t_env	*tmp;

	tmp = lst;
	if (!args[1])
		print_export(tmp);
	else
	{
		i = 0;
		while (args[++i])
		{
			if (ft_isenv(args[i][0]))
			{
				ft_error("export: ", args[i], -2);
				i++;
			}
			len = ft_strlen(args[i]) - ft_strlen(ft_strchr(args[i], '='));
			res1 = ft_substr(args[i], 0, len);
			res2 = NULL;
			if ((ft_strchr(args[i], '=')) != NULL)
				res2 = ft_strdup(&args[i][len + 1]);
			tmp = ft_getenv(lst, res1);
			if (tmp)
			{
				if (res2 != NULL)
					tmp->value = res2;
			}
			else
				ft_lstadd_back(lst, ft_lstnew(res1, res2));
		}
	}
}

void	unset_execution(t_env *lst, char **args)
{
	int	i;

	if (args[1])
	{
		i = 0;
		while (args[++i])
		{
			if (ft_isenv(args[i][0]))
			{
				ft_error("export: ", args[i], -2);
				return ;
			}
			ft_poplst(ft_getenv(lst, args[i]), lst);
		}
	}
}

void	exit_execution(void)
{
	return ;
}  

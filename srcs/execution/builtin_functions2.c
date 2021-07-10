#include "minishell.h"

void	print_export(t_env *export)
{
	while (export)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(export->key, 1);
		if (export->value != NULL)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(export->value, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
		export = export->next;
	}
}

void	export_execution(t_env *lst, char **args)
{
	t_env *tmp;
	int		i;
	int		len;
	char	*res1;
	char	*res2;

	// sort(tmp);
	// env = get_env_arr(ms);
	// bubblesort(env);
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
				return ;
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

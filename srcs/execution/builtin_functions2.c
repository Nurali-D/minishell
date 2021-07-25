#include "minishell.h"

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
	// free(name);
	// free(value);
}

void	export_execution(t_env *lst, char **args)
{
	int		i;

	if (!args[1])
		print_export(lst);
	else
	{
		i = 0;
		while (args[++i])
		{
			if (ft_isenv(args[i][0]))
			{
				ft_error("export: ", args[i], NULL, 2);
				i++;
			}
			add_export(lst, args, i, 0);
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
				ft_error("export: ", args[i], "not a valid identifier", 2);
				return ;
			}
			ft_poplst(ft_getenv(lst, args[i]), lst);
		}
	}
}

void	exit_execution(void)
{
	// free linked list
	// free structure
	// free all
	ft_putendl_fd("exit", 1);
	exit(0);
}  

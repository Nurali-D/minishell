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
	while (tmp[++i])
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

void	unset_execution(t_env *lst, char **args)
{
	int	i;

	g_status = 0;
	if (args[1])
	{
		i = 0;
		while (args[++i])
		{
			if (ft_isenv(args[i]))
			{
				env_error("unset: ", args[i], "not a valid identifier", 1);
				continue ;
			}
			ft_poplst(ft_getenv(lst, args[i]), lst);
		}
	}
}

void	exit_execution(char **args)
{
	int	i;
	(void)args;
	
	i = -1;
	g_status = 0;
	if (args[1])
	{
		while (args[1][++i])
		{
			if (!ft_isdigit(args[1][i]))
			{
				ft_error("exit: ", args[1], "numeric argument required", 255);
				break ;
			}
		}
		g_status = atoi(args[1]);
	}
	exit(g_status);
}  

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

static	size_t	ft_checksp(const char *str)
{
	size_t i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\v' ||
	str[i] == '\f' || str[i] == '\r' || str[i] == '\n')
		i++;
	return (i);
}

static	int		ft_conv(const char *str, size_t i, size_t l)
{
	int res;
	int k;

	res = 0;
	k = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (str[i] != '0')
			k++;
		if (k > 19)
		{
			if (l > 0)
				return (0);
			else
			{
				return (-1);
			}
		}
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res);
}

int				ft_datoi(const char *str)
{
	size_t	i;
	int		res;
	size_t	minus;

	if (!str)
		return (0);
	minus = 0;
	i = ft_checksp(str);
	if (str[i] == '-')
	{
		minus++;
		i++;
	}
	if (str[i] == '+' && str[i - 1] != '-')
		i++;
	res = ft_conv(str, i, minus);
	if (minus > 0)
		res = res * -1;
	return (res);
}

void	exit_execution(char **args)
{
	int	i;
	(void)args;
	
	i = -1;
	g_status = 0;
	ft_putendl_fd("exit", 1);
	if (args[1])
	{
		while (args[1][++i])
		{
			if (!ft_isdigit(args[1][i]))
			{
				ft_error("exit: ", args[1], "numeric argument required", 255);
				exit(g_status);
			}
		}
		if (args[2])
		{
			ft_error("exit: ", NULL, "too many arguments", 1);
			return ;
		}
	}
	exit(g_status);
}

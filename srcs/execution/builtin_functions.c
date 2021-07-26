#include "minishell.h"

void	echo_execution(char **args)
{
	int	i;

	i = 1;
	g_status = 0;
	while (args[i] && (ft_strcmp(args[i], "-n")) == 0)
		i++;
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[++i])
			ft_putchar_fd(' ', 1);
	}
	if (!(args[1]) || (ft_strcmp(args[1], "-n")) != 0)
		ft_putchar_fd('\n', 1);
}

void	cd_execution(char **args, t_env *head)
{
	int		i;
	t_env	*tmp;

	g_status = 0;
	tmp = ft_getenv(head, "OLDPWD");
	if (tmp)
	{
		tmp->value = getcwd(NULL, 0);
		// if (tmp->value == NULL)
		// 	ft_error("cd: ", args[1], strerror(errno), 1);
		i = chdir(args[1]);
		if (i == -1)
			ft_error("cd: ", args[1], strerror(errno), 1);
	}
	tmp = ft_getenv(head, "PWD");
	if (tmp)
	{
		if (tmp->value == NULL)
			ft_error("cd: ", args[1], strerror(errno), 1);
		tmp->value = getcwd(NULL, 0);
	}
}

void	pwd_execution(void)
{
	char	*path;

	g_status = 0;
	path = NULL;
	path = getcwd(NULL, 0);
	ft_putendl_fd(path, 1);
	free(path);
	path = NULL;
}

void	env_execution(t_env *env, char **args)
{
	g_status = 0;
	if (args[1])
		ft_error("env: ", args[1], strerror(ENOENT), 127);
	else
	{
		while (env)
		{
			if (env->value)
			{
				ft_putstr_fd(env->key, 1);
				ft_putchar_fd('=', 1);
				ft_putstr_fd(env->value, 1);
				ft_putchar_fd('\n', 1);
			}
			env = env->next;
		}
	}
}

#include "minishell.h"

void	echo_execution(char **args, int i)
{
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
	printf("\e[1;92mbuilt-in function\n\e[0m");
}

void	cd_execution(char **args, t_env *head)
{
	int		i;
	t_env	*tmp;

	tmp = ft_getcwd(head, "OLDPWD");
	tmp->value = getcwd(NULL, 0);
	if (!args[1])
	{
		printf("\e[1;92mbuilt-in function\n\e[0m");
		tmp = ft_getcwd(head, "HOME");
		chdir(tmp->value);
	}
	else
	{
		i = chdir(args[1]);
		if (i == -1)
			cd_error("cd: ", args[1], errno);
	}
	tmp = ft_getcwd(head, "PWD");
	tmp->value = getcwd(NULL, 0);
}

void	pwd_execution(void)
{
	char	*path;

	path = NULL;
	path = getcwd(NULL, 0);
	if (path == NULL)
		return ;
	ft_putendl_fd(path, 1);
	free(path);
	path = NULL;
	printf("\e[1;92mbuilt-in function\n\e[0m");
}

void	env_execution(t_env *env)
{
	while (env)
	{
		ft_putstr_fd(env->key, 1);
		ft_putchar_fd('=', 1);
		ft_putstr_fd(env->value, 1);
		ft_putchar_fd('\n', 1);
		env = env->next;
	}
	printf("\e[1;92mbuilt-in function\n\e[0m");
}

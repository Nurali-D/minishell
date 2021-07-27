#include "minishell.h"

void	cd_execution(char **args, t_env *head)
{
	int		i;
	t_env	*tmp;

	g_status = 0;
	tmp = ft_getenv(head, "OLDPWD");
	if (tmp)
	{
		tmp->value = getcwd(NULL, 0);
		i = chdir(args[1]);
		if (i == -1)
			ft_error(args[0], args[1], strerror(errno), 1);
	}
	tmp = ft_getenv(head, "PWD");
	if (tmp)
	{
		if (tmp->value == NULL)
			ft_error(args[0], args[1], strerror(errno), 1);
		tmp->value = getcwd(NULL, 0);
	}
}

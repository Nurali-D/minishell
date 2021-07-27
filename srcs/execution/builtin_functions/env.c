#include "minishell.h"

void	env_execution(t_env *env, char **args)
{
	g_status = 0;
	if (args[1])
		ft_error(args[0], args[1], strerror(ENOENT), 127);
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

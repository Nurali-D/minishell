#include "minishell.h"

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

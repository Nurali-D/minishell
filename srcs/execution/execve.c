#include "minishell.h"

void	execve_absolute_path(t_msh *ms, t_env *head)
{
	char	**env;

	if (!(check_stat(ms->tokens->args)))
		return ;
	env = get_env_arr(head);
	if (ms->nc == 1)
	{
		ft_execve(ms->tokens->args, env);
		return ;
	}
	execve(ms->tokens->args[0], ms->tokens->args, env);
}

int	execve_relative_path(t_msh *ms, t_env *head)
{
	char	**env;
	char	**path;
	t_env	*tmp;

	tmp = NULL;
	path = NULL;
	tmp = ft_getenv(head, "PATH");
	if (tmp == NULL)
	{
		ft_error(ms->tokens->args[0], NULL, strerror(2), 127);
		return (1);
	}
	path = ft_split(tmp->value, ':');
	env = get_env_arr(head);
	if ((check_path(ms, path, env)) == 1)
		return (1);
	return (0);
}

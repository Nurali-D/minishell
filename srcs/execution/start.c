#include "minishell.h"

void	check_functions(t_msh *ms, t_env *env_list)
{
	if (ms->tokens->args[0])
	{
		if ((ft_strcmp(ms->tokens->args[0], "echo")) == 0)
			echo_execution(ms->tokens->args);
		else if ((ft_strcmp(ms->tokens->args[0], "cd")) == 0)
			cd_execution(ms->tokens->args, env_list);
		else if ((ft_strcmp(ms->tokens->args[0], "pwd")) == 0)
			pwd_execution();
		else if ((ft_strcmp(ms->tokens->args[0], "export")) == 0)
			export_execution(env_list, ms->tokens->args);
		else if ((ft_strcmp(ms->tokens->args[0], "unset")) == 0)
			unset_execution(env_list, ms->tokens->args);
		else if ((ft_strcmp(ms->tokens->args[0], "env")) == 0)
			env_execution(env_list, ms->tokens->args);
		else if ((ft_strcmp(ms->tokens->args[0], "exit")) == 0)
			exit_execution(ms->tokens->args);
		else if ((ft_strchr(ms->tokens->args[0], '/')) != NULL)
			execve_absolute_path(ms, env_list);
		else if ((execve_relative_path(ms, env_list)))
			;
		else
			ft_error(ms->tokens->args[0], NULL, "command not found", 127);
	}
}

#include "minishell.h"

void	check_functions(t_msh *ms)
{
	if ((ft_strcmp(ms->tokens->args[0], "echo")) == 0)
		echo_execution(ms->tokens->args);
	else if ((ft_strcmp(ms->tokens->args[0], "cd")) == 0)
		cd_execution(ms->tokens->args, ms->env_list);
	else if ((ft_strcmp(ms->tokens->args[0], "pwd")) == 0)
		pwd_execution();
	else if ((ft_strcmp(ms->tokens->args[0], "export")) == 0)
		export_execution(ms->env_list, ms->tokens->args);
	else if ((ft_strcmp(ms->tokens->args[0], "unset")) == 0)
		unset_execution(ms->env_list, ms->tokens->args);
	else if ((ft_strcmp(ms->tokens->args[0], "env")) == 0)
		env_execution(ms->env_list, ms->tokens->args);
	else if ((ft_strcmp(ms->tokens->args[0], "exit")) == 0)
		exit_execution();
	else if ((ft_strchr(ms->tokens->args[0], '/')) != NULL)
		check_fullpath_functions(ms->tokens->args, ms->env_list);
	else if ((check_execve_functions(ms->tokens->args, ms->env_list)))
		;
	else
		ft_error(ms->tokens->args[0], "", "command not found", 0);
}

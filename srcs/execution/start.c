#include "minishell.h"

void	check_functions(t_token *token, t_env *env_list)
{
	if ((ft_strcmp(token->args[0], "echo")) == 0)
		echo_execution(token->args);
	else if ((ft_strcmp(token->args[0], "cd")) == 0)
		cd_execution(token->args, env_list);
	else if ((ft_strcmp(token->args[0], "pwd")) == 0)
		pwd_execution();
	else if ((ft_strcmp(token->args[0], "export")) == 0)
		export_execution(env_list, token->args);
	else if ((ft_strcmp(token->args[0], "unset")) == 0)
		unset_execution(env_list, token->args);
	else if ((ft_strcmp(token->args[0], "env")) == 0)
		env_execution(env_list, token->args);
	else if ((ft_strcmp(token->args[0], "exit")) == 0)
		exit_execution(token->args);
	else if ((ft_strchr(token->args[0], '/')) != NULL)
		check_fullpath_functions(token->args, env_list);
	else if ((check_execve_functions(token->args, env_list)))
		;
	else
		ft_error(token->args[0], "", "command not found", 127);
}

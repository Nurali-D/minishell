#include "minishell.h"

int	check_execve_functions(t_msh *ms, t_env *head)
{
	char			**env;
	DIR				*dir;
	struct dirent	*dir_entry;
	char			**path;
	t_env			*tmp;
	int				i;
	int				len;
	pid_t			pid;

	tmp = ft_getenv(head, "PATH");
	path = ft_split(tmp->value, ':');
	env = get_env_arr(ms->env_list);
	i = -1;
	while (path[++i])
	{
		if ((ft_strncmp(ms->tokens->args[0], path[i], ft_strlen(path[i]))) == 0)
		{
			dir = opendir(path[i]);
			len = ft_strlen(path[i]);
			dir_entry = readdir(dir);
			while (dir_entry != NULL)
			{
				if ((ft_strcmp(&ms->tokens->args[0][len + 1],
						dir_entry->d_name)) == 0)
				{
					pid = fork();
					if (pid != 0)
						wait(0);
					if (pid == 0)
						execve(ms->tokens->args[0], ms->tokens->args, env);
					return (1);
				}
				dir_entry = readdir(dir);
			}
			closedir(dir);
		}
	}
	i = -1;
	while (path[++i])
	{
		dir = opendir(path[i]);
		if (dir != NULL)
		{
			dir_entry = readdir(dir);
			while (dir_entry != NULL)
			{
				if ((ft_strcmp(ms->tokens->args[0], dir_entry->d_name)) == 0)
				{
					ms->tokens->args[0] = triplejoin(path[i],
							"/", ms->tokens->args[0]);
					pid = fork();
					if (pid != 0)
						wait(0);
					if (pid == 0)
						execve(ms->tokens->args[0], ms->tokens->args, env);
					return (1);
				}
				dir_entry = readdir(dir);
			}
			closedir(dir);
		}
	}
	return (0);
}

void	check_functions(t_msh *ms)
{
	// if ((ft_strchr(ms->tokens->args[0], '/')) != NULL)
	// 	ft_error(ms->tokens->args[0], "\0", 2);
	if ((ft_strcmp(ms->tokens->args[0], "echo")) == 0)
		echo_execution(ms->tokens->args, 1);
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
	else if ((check_execve_functions(ms, ms->env_list)))
		;
	else
		ft_error(ms->tokens->args[0], NULL, -1);
}

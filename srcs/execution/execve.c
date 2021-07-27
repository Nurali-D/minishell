 #include "minishell.h"

int	check_stat(char **args)
{
	int			status;
	struct stat	buf;

	status = stat(args[0], &buf);
	if (status == 0)
	{
		if ((buf.st_mode & S_IFDIR))
		{
			ft_error(args[0], NULL, "is a directory",  126);
			return (0);
		}
		else if (!(buf.st_mode & S_IXUSR))
		{
			ft_error(args[0], NULL, strerror(EACCES), 126);
			return (0);
		}
	}
	return (1);
}

void	check_fullpath_functions(char **args, t_env *head, int nc)
{
	int			err;
	int			status;
	char		**env;
	pid_t		pid;

	if (!(check_stat(args)))
		return ;
	env = get_env_arr(head);
	if (nc == 1)
	{
		pid = fork();
		if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			err = execve(args[0], args, env);
			if (err == -1)
			{
				ft_error(args[0], NULL, strerror(errno),  0);
				return ;
			}
		}
		if (pid != 0)
		{
			waitpid(pid, &status, WUNTRACED);
			get_status(status);
		}
		return ;
	}
	err = execve(args[0], args, env);
	if (err == -1)
	{
		ft_error(args[0], NULL, strerror(errno),  0);
		return ;
	}
}

int	check_execve_functions(char **args, t_env *head, int nc)
{
	int				i;
	int				status;
	char			**env;
	char			**path;
	pid_t			pid;
	t_env			*tmp;
	DIR				*dir;
	struct dirent	*dir_entry;

	tmp = NULL;
	path = NULL;
	tmp = ft_getenv(head, "PATH");
	if (tmp == NULL)
	{
		ft_error(args[0], NULL, strerror(2), 127);
		return (1);
	}
	path = ft_split(tmp->value, ':');
	env = get_env_arr(head);
	i = -1;
	while (path[++i])
	{
		dir = opendir(path[i]);
		if (dir != NULL)
		{
			dir_entry = readdir(dir);
			while (dir_entry != NULL)
			{
				if ((ft_strcmp(args[0], dir_entry->d_name)) == 0)
				{
					args[0] = triplejoin(path[i], "/", args[0]);
					if (nc == 1)
					{
						pid = fork();
						if (pid == 0)
						{
							signal(SIGINT, SIG_DFL);
							signal(SIGQUIT, SIG_DFL);
							execve(args[0], args, env);
						}
						if (pid != 0)
						{
							waitpid(pid, &status, WUNTRACED);
							get_status(status);
						}
						return (1);
					}
					execve(args[0], args, env);
					// return (1);
				}
				dir_entry = readdir(dir);
			}
			closedir(dir);
		}
	}
	return (0);
}

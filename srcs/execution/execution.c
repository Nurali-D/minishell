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
			ft_error(args[0], "", "is a directory",  0);
			return (0);
		}
		else if (!(buf.st_mode & S_IXUSR))
		{
			ft_error(args[0], "", strerror(EACCES),  0);
			return (0);
		}
	}
	return (1);
}

void	check_fullpath_functions(char **args, t_env *head)
{
	int			status;
	char		**env;
	pid_t		pid;

	if (!(check_stat(args)))
		return ;
	env = get_env_arr(head);
	pid = fork();
	if (pid != 0)
		wait(0);
	if (pid == 0)
	{
		// signal(SIGINT, SIG_DFL);
		// signal(SIGQUIT, SIG_DFL);
		status = execve(args[0], args, env);
		if (status == -1)
		{
			ft_error(args[0], "", strerror(errno),  0);
			return ;
		}
	}
}

int	check_execve_functions(char **args, t_env *head)
{
	int				i;
	char			**env;
	char			**path;
	pid_t			pid;
	t_env			*tmp;
	DIR				*dir;
	struct dirent	*dir_entry;

	tmp = NULL;
	path = NULL;
	tmp = ft_getenv(head, "PATH");
	if (tmp != NULL)
	{
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
						pid = fork();
						if (pid != 0)
							wait(0);
						if (pid == 0)
						{
							// signal(SIGINT, SIG_DFL);
							// signal(SIGQUIT, SIG_DFL);
							execve(args[0], args, env);
						}
						return (1);
					}
					dir_entry = readdir(dir);
				}
				closedir(dir);
			}
		}
	}
	return (0);
}

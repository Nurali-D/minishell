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
			ft_error(args[0], NULL, "is a directory", 126);
			return (0);
		}
		else if (!(buf.st_mode & S_IXUSR))
		{
			ft_error(args[0], NULL, strerror(EACCES), 126);
			return (0);
		}
	}
	if (status == -1)
	{
		ft_error(args[0], NULL, strerror(errno), 127);
		return (0);
	}
	return (1);
}

void	ft_execve(char **args, char **env)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		execve(args[0], args, env);
	}
	if (pid != 0)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		waitpid(pid, &status, WUNTRACED);
		get_status(status);
	}
}

int	check_dir_entry(t_msh *ms, char **env, char *path, struct dirent *dir)
{
	if ((ft_strcmp(ms->tokens->args[0], dir->d_name)) == 0)
	{
		ms->tokens->args[0] = triplejoin(path, "/", ms->tokens->args[0]);
		if (ms->nc == 1)
		{
			ft_execve(ms->tokens->args, env);
			return (1);
		}
		execve(ms->tokens->args[0], ms->tokens->args, env);
	}
	return (0);
}

int	check_path(t_msh *ms, char **path, char **env)
{
	int				i;
	DIR				*dir;
	struct dirent	*dir_entry;

	i = -1;
	while (path[++i])
	{
		dir = opendir(path[i]);
		if (dir != NULL)
		{
			dir_entry = readdir(dir);
			while (dir_entry != NULL)
			{
				if ((check_dir_entry(ms, env, path[i], dir_entry)) == 1)
					return (1);
				dir_entry = readdir(dir);
			}
			closedir(dir);
		}
	}
	return (0);
}

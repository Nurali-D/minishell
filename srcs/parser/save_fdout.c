#include "minishell.h"

int	is_regular_file(char *path)
{
	struct stat	buf;

	stat(path, &buf);
	return (S_ISREG(buf.st_mode));
}

int	is_directory(char *path)
{
	struct stat	buf;

	stat(path, &buf);
	return (S_ISDIR(buf.st_mode));
}

int	permission_to_write(char *filename)
{
	struct stat	buf;

	stat(filename, &buf);
	return (buf.st_mode & S_IWUSR);
}

char	*check_outfiles(char **filenames)
{
	int	i;
	int	c;

	i = -1;
	while (filenames[++i])
	{
		if (!file_exist(filenames[i]))
			close(open(filenames[i], O_RDWR | O_CREAT, 0644));
		c = is_directory(filenames[i]);
		if (c)
		{
			write(STDERR_FILENO, "bash: ", 6);
			write(STDERR_FILENO, filenames[i], ft_strlen(filenames[i]));
			write(STDERR_FILENO, ": Is a directory\n", 17);
			return (NULL);
		}
		if (!permission_to_write(filenames[i]))
		{
			write(STDERR_FILENO, "bash: ", 6);
			write(STDERR_FILENO, filenames[i], ft_strlen(filenames[i]));
			write(STDERR_FILENO, ": Permission denied\n", 20);
			return (NULL);
		}
	}
	return (filenames[--i]);
}

void	save_fdout_to_token(char **filenames, char **append,
							t_token *token, int last)
{
	char	*file1;
	char	*file2;

	file1 = NULL;
	file2 = NULL;
	if (filenames)
		file1 = check_outfiles(filenames);
	if (append)
		file2 = check_outfiles(append);
	if ((file1 == NULL && filenames != NULL)
		|| (file2 == NULL && append != NULL))
	{
		unlink("heredoc_temp");
		token->fd_err = -1;
		return ;
	}
	if (last == 1)
		token->fd_out = open(file1, O_WRONLY | O_TRUNC);
	else if (last == 2)
		token->fd_out = open(file2, O_WRONLY | O_APPEND);
}

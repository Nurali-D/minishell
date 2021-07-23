#include "minishell.h"

int	file_exist(char *filename)
{
	struct stat	buf;

	return (stat(filename, &buf) == 0);
}

int	permission_to_read(char *filename)
{
	struct stat	buf;

	stat(filename, &buf);
	return (buf.st_mode & S_IRUSR);
}

char	*check_infiles(char **filenames)
{
	int	i;

	i = -1;
	while (filenames[++i])
	{
		if (!file_exist(filenames[i]))
		{
			write(STDERR_FILENO, "bash: ", 6);
			write(STDERR_FILENO, filenames[i], ft_strlen(filenames[i]));
			write(STDERR_FILENO, ": No such file or directory\n", 28);
			return (NULL);
		}
		if (!permission_to_read(filenames[i]))
		{
			write(STDERR_FILENO, "bash: ", 6);
			write(STDERR_FILENO, filenames[i], ft_strlen(filenames[i]));
			write(STDERR_FILENO, ": Permission denied\n", 20);
			return (NULL);
		}
	}
	return (filenames[--i]);
}

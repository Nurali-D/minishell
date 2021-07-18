#include "minishell.h"

int	gnl(char **line)
{
	int		i;
	int		ret;
	char	*buf;

	buf = (char *)malloc(sizeof(char) * 10000);
	*line = buf;
	i = 0;
	write(STDOUT_FILENO, "> ", 2);
	ret = read(STDIN_FILENO, &buf[i], 1);
	while (ret > 0 && buf[i] != '\n')
	{
		i++;
		ret = read(STDIN_FILENO, &buf[i], 1);
	}
	buf[i] = '\0';
	return (ret);
}

void	read_from_heredoc(char **hrd_lim)
{
	int		i;
	char	*line;
	int		fd_heredoc;

	i = -1;
	while (hrd_lim && hrd_lim[++i])
	{
		fd_heredoc = open("heredoc_temp",  O_RDWR | O_CREAT | O_TRUNC, 0644);
		while (gnl(&line) > 0)
		{
			if (!ft_strcmp(line, hrd_lim[i]))
			{
				free(line);
				close(fd_heredoc);
				break ;
			}
			write(fd_heredoc, line, ft_strlen(line));
			write(fd_heredoc, "\n", 1);
			free(line);
		}
		// close(fd_heredoc);
		if (hrd_lim[i + 1])
			unlink("heredoc_temp");
	}
}

#include "minishell.h"

void	cut_redirection_from_str(char **names, char **str, int n)
{
	int		i;
	char	*address;
	char	*after;

	i = -1;
	while (names[++i])
	{
		address = ft_strnstr(*str, names[i], ft_strlen(*str));
		after = address + ft_strlen(names[i]);
		ft_memmove(address - n, after, ft_strlen(after) + 1);
	}
}

void	save_fdin_to_token(char **filenames, char **heredoc_limiters,
							t_token *token, int last)
{
	char	*file;

	file = NULL;
	if (heredoc_limiters)
		read_from_heredoc(heredoc_limiters);
	if (filenames)
		file = check_infiles(filenames);
	if (file == NULL && filenames != NULL)
	{
		unlink("heredoc_temp");
		token->fd_err = -1;
		return ;
	}
	if (last == 1)
	{
		unlink("heredoc_temp");
		token->fd_in = open(file, O_RDONLY);
	}
	else if (last == 2)
		token->fd_in = open("heredoc_temp", O_RDONLY);
}

int	find_last_redirection(char *str, char c)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (i >= 0)
	{
		if (str[i] == c && (i - 1) >= 0 && str[i - 1] != c)
			return (1);
		else if (str[i] == c && i == 0)
			return (1);
		else if (str[i] == c && (i - 1) >= 0 && str[i - 1] == c)
			return (2);
		i--;
	}
	return (0);
}

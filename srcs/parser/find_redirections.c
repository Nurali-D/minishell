#include "minishell.h"

char	**get_filenames_in(char **str, int s)
{
	char	**filenames;
	int		i;
	int		j;
	int		k;

	filenames = (char **)malloc(sizeof(char *) * (s + 1));
	i = -1;
	k = 0;
	while ((*str)[++i])
	{
		if ((*str)[i] == '<' && (*str)[i + 1] != '<' && (*str)[i - 1] != '<')
		{
			j = i;
			while ((*str)[++j])
			{
				if ((*str)[j] == ' ' || (*str)[j] == '<')
					break ;
			}
			filenames[k] = ft_substr((*str), i + 1, j - i - 1);
			printf("%s\n", filenames[k]);
			k++;
		}
	}
	filenames[k] = NULL;
	return (filenames);
}

char	**get_heredoc_limiters(char **str, int d)
{
	char	**heredoc_limiters;
	int		i;
	int		j;
	int		k;

	heredoc_limiters = (char **)malloc(sizeof(char *) * (d + 1));
	i = -1;
	k = 0;
	while ((*str)[++i])
	{
		if ((*str)[i] == '<' && (*str)[i + 1] == '<')
		{
			i++;
			j = i;
			while ((*str)[++j])
			{
				if ((*str)[j] == ' ' || (*str)[j] == '<')
					break ;
			}
			heredoc_limiters[k] = ft_substr((*str), i + 1, j - i - 1);
			k++;
		}
	}
	heredoc_limiters[k] = NULL;
	return (heredoc_limiters);
}

void	save_fd_in(char **str, t_token *token, int s, int d)
{
	char	**filenames_in;
	char	**heredoc_limiters;
	int		last_red;

	filenames_in = NULL;
	heredoc_limiters = NULL;
	last_red = find_last_redirection(*str, '<');
	if (s)
	{
		filenames_in = get_filenames_in(str, s);
		cut_redirection_from_str(filenames_in, str, 1);
	}
	if (d)
	{
		heredoc_limiters = get_heredoc_limiters(str, d);
		cut_redirection_from_str(heredoc_limiters, str, 2);
	}
	save_fd_to_token(filenames_in, heredoc_limiters, token, last_red);
}

// void	save_fd_out(char **str, t_token *s_token, int s, int d)
// {
// 	char	**filenames_out;
// 	char	**filenames_append;


// }

void	find_redirections(char **str, t_token *token, char c)
{
	int	i;
	int	single_red;
	int	double_red;

	i = 0;
	single_red = 0;
	double_red = 0;
	while (i < (int)ft_strlen(*str) && (*str)[i])
	{
		if ((*str)[i] == c && (*str)[i + 1] != c)
			single_red++;
		if ((*str)[i] == c && (*str)[i + 1] == c)
		{
			double_red++;
			i++;
		}
		i++;
	}
	if (c == '<' && (single_red || double_red))
		save_fd_in(str, token, single_red, double_red);
	// else
	// 	save_fd_out(str, token, single_red, double_red);
}

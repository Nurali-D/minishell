#include "minishell.h"

char	**get_filenames(char **str, int s, char c)
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
		if ((*str)[i] == c && (*str)[i + 1] != c && (*str)[i - 1] != c)
		{
			j = i;
			while ((*str)[++j])
			{
				if ((*str)[j] == ' ' || (*str)[j] == c)
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

char	**get_limiters_files(char **str, int d, char c)
{
	char	**lims_files;
	int		i;
	int		j;
	int		k;

	lims_files = (char **)malloc(sizeof(char *) * (d + 1));
	i = -1;
	k = 0;
	while ((*str)[++i])
	{
		if ((*str)[i] == c && (*str)[i + 1] == c)
		{
			i++;
			j = i;
			while ((*str)[++j])
			{
				if ((*str)[j] == ' ' || (*str)[j] == c)
					break ;
			}
			lims_files[k] = ft_substr((*str), i + 1, j - i - 1);
			k++;
		}
	}
	lims_files[k] = NULL;
	return (lims_files);
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
		filenames_in = get_filenames(str, s, '<');
		cut_redirection_from_str(filenames_in, str, 1);
	}
	if (d)
	{
		heredoc_limiters = get_limiters_files(str, d, '<');
		cut_redirection_from_str(heredoc_limiters, str, 2);
	}
	save_fdin_to_token(filenames_in, heredoc_limiters, token, last_red);
}

void	save_fd_out(char **str, t_token *token, int s, int d)
{
	char	**filenames_out;
	char	**filenames_append;
	int		last_red;

	filenames_out = NULL;
	filenames_append = NULL;
	last_red = find_last_redirection(*str, '>');
	if (s)
	{
		filenames_out = get_filenames(str, s, '>');
		cut_redirection_from_str(filenames_out, str, 1);
	}
	if (d)
	{
		filenames_append = get_limiters_files(str, d, '>');
		cut_redirection_from_str(filenames_append, str, 2);
	}
	save_fdout_to_token(filenames_out, filenames_append, token, last_red);
}

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
	else if (c == '>' && (single_red || double_red))
		save_fd_out(str, token, single_red, double_red);
}

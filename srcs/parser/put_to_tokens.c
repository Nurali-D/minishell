#include "minishell.h"

void	delete_spaces_after_redirection(char **str)
{
	int	i;
	int	j;

	i = -1;
	while ((*str)[++i])
	{
		if (((*str)[i] == '<' && (*str)[i + 1] != '<')
			|| ((*str)[i] == '>' && (*str)[i + 1] != '>'))
		{
			i++;
			j = i;
			while ((*str)[i] == ' ')
				i++;
			memmove(&(*str)[j], &(*str)[i], strlen(&(*str)[i]) + 1);
			i = j;
		}
	}
}

char	**get_args_fd(char *str, t_token *token)
{
	char	**ret;

	delete_spaces_after_redirection(&str);
	find_redirections(&str, token, '<');
	find_redirections(&str, token, '>');
	ret = ft_split(str, ' ');
	return (ret);
}

void	put_to_tokens_list(t_msh *ms, t_token *new)
{
	t_token	*tmp;

	tmp = ms->tokens;
	while (tmp)
	{
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	if (tmp)
		tmp->next = new;
	else
		ms->tokens = new;
}

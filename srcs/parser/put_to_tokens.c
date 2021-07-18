#include "minishell.h"

char	**get_args_fd(char *str, t_token *token)
{
	char	**ret;

	find_redirections(&str, token, '<');
	// find_redirections(&str, token, '>');
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


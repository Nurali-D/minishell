#include "minishell.h"

void	change_175(char **args)
{
	int	i;
	int	j;

	i = -1;
	while (args[++i])
	{
		j = -1;
		while (args[i][++j])
		{
			if (args[i][j] == (char)175)
				args[i][j] = ' ';
		}
	}
}

void	replace_175(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		change_175(tmp->args);
		tmp = tmp->next;
	}
}

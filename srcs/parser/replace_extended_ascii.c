#include "minishell.h"

void	change_extended_ascii(char **args)
{
	int	i;
	int	j;

	i = -1;
	while (args[++i])
	{
		j = -1;
		while (args[i][++j])
		{
			if (args[i][j] == (char)169)
				args[i][j] = ' ';
			else if (args[i][j] == (char)174)
				args[i][j] = '<';
			else if (args[i][j] == (char)175)
				args[i][j] = '>';
		}
	}
}

void	replace_extended_ascii(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		change_extended_ascii(tmp->args);
		tmp = tmp->next;
	}
}

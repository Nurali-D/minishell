#include "minishell.h"

void	change_175(char **args)
{
	int	i;
	int	j;

	i = 0;
	while (args[++i])
	{
		j = -1;
		while (args[i][++j])
		{
			if (args[i][j] == '=' && args[i][j + 1] == (char)175)
				ft_memmove(&args[i][j + 1], &args[i][j + 2],
					ft_strlen(&args[i][j + 2]) + 1);
			if (args[i][j] == (char)175)
				args[i][j] = ' ';
		}
	}
}

void	replace_export175(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (!ft_strcmp(tmp->args[0], "export"))
			change_175(tmp->args);
		tmp = tmp->next;
	}
}

#include "minishell.h"

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;
	t_token	*tmp2;
	int		i;

	tmp = tokens;
	while (tmp)
	{
		i = -1;
		while(tmp->args && tmp->args[++i])
			free(tmp->args[i]);
		tmp2 = tmp;
		tmp = tmp->next;
		free(tmp2);
	}
	if (tmp)
		free(tmp);
}

void	parse_execute(t_msh *ms)
{
	while (1)
	{
		ms->line = readline(ms->prompt);
		if (ms->line[0] != '\0')
		{
			add_history(ms->line);
			if (parse_line(ms) == 0)
				check_builtin_functions(ms);
		}
		free_tokens(ms->tokens);
		ms->tokens = NULL;
		if (ms->line)
			free(ms->line);
	}
}

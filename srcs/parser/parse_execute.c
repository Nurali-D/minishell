#include "minishell.h"

void	parse_execute(t_msh *ms)
{
	while (1)
	{
		ms->line = readline(ms->prompt);
		if (ms->line[0] != '\0')
			add_history(ms->line);
		parse_line(ms);
	}
}

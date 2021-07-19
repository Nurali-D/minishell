#include "minishell.h"

int	check_for_syntax_errors(t_msh *ms)
{
	int	i;

	i = -1;
	(void)ms;
	while (ms->line && ms->line[++i])
	{
		if (ms->line[i] == '\'' && check_single_quotes(ms->line, &i) == 1)
			return (1);
		else if (ms->line[i] == '"' && check_double_quotes(ms->line, &i) == 1)
			return (1);
	}
	return (0);
}

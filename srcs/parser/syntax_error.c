#include "minishell.h"

void	check_semicolon(t_msh *ms, int *i)
{
	int	j;

	j = *i;
	while (j != 0 && ms->line[j])
	{
		--j;
		if (ms->line[j] != ';' && ms->line[j] != ' ')
			return ;
		if (ms->line[j] == ';')
		{
			if (ms->line[j + 1] == ';' || ms->line[j - 1] == ';')
				error_function(ms, "syntax error near unexpected token `;;'");
			else
				error_function(ms, "syntax error near unexpected token `;'");
			*i = ft_strlen(ms->line);
		}
	}
	if (j == 0 && (ms->line[j] == ';' || ms->line[j] == ' '))
	{
		if (ms->line[j + 1] == ';')
			error_function(ms, "syntax error near unexpected token `;;'");
		else
			error_function(ms, "syntax error near unexpected token `;'");
		*i = ft_strlen(ms->line);
	}
}

// void	check_pipe(t_msh *ms, int *i)
// {

// }

void	check_for_syntax_errors(t_msh *ms)
{
	int	i;

	i = -1;
	(void)ms;
	while (ms->line[++i])
	{
		if (ms->line[i] == ';')
			check_semicolon(ms, &i);
		// else if (ms->line[i] == '|')
		// 	check_pipe(ms, &i);
		
	}
}
#include "minishell.h"




// void	treat_semicolon(t_msh *ms)
// {

// }

// void	treat_redirection(t_msh *ms)
// {

// }

// void	treat_pipe(t_msh *ms)
// {

// }



void	parse_line(t_msh *ms)
{
	int	i = -1;

	check_for_syntax_errors(ms);
	while (ms->line[++i])
	{
		if (ms->line[i] == '\'')
			ms->line = treat_single_quotes(ms->line, &i);
		else if (ms->line[i] == '\\')
			ms->line = treat_slash(ms->line, &i);
		else if (ms->line[i] == '"')
			ms->line = treat_double_quotes(ms->line, &i, ms->env_list);
		else if (ms->line[i] == '$')
			ms->line = treat_dollar(ms->line, &i, ms->env_list);
	// 	else if (ms->line[i] == ';')
	// 		treat_semicolon(ms);
	// 	else if (ms->line[i] == "|")
	// 		treat_pipe(ms);
	// 	else if (ms->line[i] == ">" || ms->line[i] == "<")
	// 		treat_redirection(ms);
	// 	else
		// i++;
	}
	printf("%s\n", ms->line);
}

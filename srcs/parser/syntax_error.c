#include "minishell.h"

int	check_single_quotes(char *line, int i)
{
	while (line && line[++i])
	{
		if (line[i] == '\'')
			return 0;
	}
	printf("Not interpret unclosed quotes!\n");
	return 1;
}

int	check_double_quotes(char *line, int i)
{
	while (line && line[++i])
	{
		if (line[i] == '\'' && i > 0 && line[i - 1] != '\\')
			return 0;
	}
	printf("Not interpret unclosed quotes!\n");
	return 1;
}

int	check_semicolon(void)
{
	printf("Not interpret semicolon!\n");
	return (1);
}

int	check_for_syntax_errors(t_msh *ms)
{
	int	i;
	// int	j;

	// j = 0;
	i = -1;
	(void)ms;
	while (ms->line && ms->line[++i])
	{
		if (ms->line[i] == '\'' && check_single_quotes(ms->line, i) == 1)
			return (1);
		else if (ms->line[i] == '\\')
			i += 1;
		else if (ms->line[i] == '"' && check_double_quotes(ms->line, i) == 1)
			return (1);
		// else if (ms->line[i] == '$')
		// 	ms->line = treat_dollar(ms->line, &i, ms->env_list);
		else if (ms->line[i] == ';')
			return (check_semicolon());
		// else if (ms->line[i] == '|')
		// {
		// 	check_pipe(ms->line, i);
		// 	j = i + 1;
		// }
		// else if (ms->line[i] == '>' || ms->line[i] == '<')
		// {
		// 	check_redirections(ms, &i, j);
		// 	j = i + 1;
		// }
	}
	return (0);
}
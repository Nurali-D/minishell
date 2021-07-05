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
	printf("Not interpret ;\n");
	return (1);
}

int is_separator(char c)
{
	if (c == ' ' || c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	check_pipe(char *line, int i)
{
	int	j;
	int k;

	k = 0;
	j = i;
	while (j >= 0 && line[--j])
		if (ft_isprint(line[j]) && !is_separator(line[j]))
		{
			k = 1;
			break ;
		}
	j = i;
	while (j < (int)ft_strlen(line) && line[++j])
		if (ft_isprint(line[j]) && !is_separator(line[j]))
		{
			k++;
			break ;
		}
	if (k == 2)
		return (0);
	if (k != 2 && (int)ft_strlen(line) > 0 && line[i + 1] == '|')
		printf("syntax error near unexpected token `||'\n");
	else
		printf("syntax error near unexpected token `|'\n");
	return (1);
}

int	check_for_syntax_errors(t_msh *ms)
{
	int	i;

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
		else if (ms->line[i] == ';')
			return (check_semicolon());
		else if (ms->line[i] == '|' && check_pipe(ms->line, i) == 1)
			return (1);
		// else if (ms->line[i] == '>' || ms->line[i] == '<')
		// 	check_redirections(ms, &i, j);
	}
	return (0);
}

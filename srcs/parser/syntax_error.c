#include "minishell.h"

int	check_before_pipe(char *str, int i)
{
	int	k;

	k = i;
	while (k > 0 && str[k])
	{
		k--;
		if (ft_isprint(str[k]) && (str[k] != ' '
				&& str[k] != '|' && str[k] != '<' && str[k] != '>'))
			return (0);
		else if (str[k] == '|' || str[k] == '<' || str[k] == '>')
		{
			write(STDERR_FILENO, "bash: syntax error near unexpected token `|'\n", 45);
			return (1);
		}
	}
	write(STDERR_FILENO, "bash: syntax error near unexpected token `|'\n", 45);
	return (1);
}

int	check_after_pipe(char *str, int i)
{
	int	k;

	k = i;
	while (str[++k])
	{
		if (ft_isprint(str[k]) && (str[k] != ' '
				&& str[k] != '|' && str[k] != '<' && str[k] != '>'))
			return (0);
		else if (str[k] == '|')
		{
			write(STDERR_FILENO, "bash: syntax error near unexpected token `|'\n", 45);
			return (1);
		}
		else if (str[k] == '<' || str[k] == '>')
		{
			write(STDERR_FILENO, "bash: syntax error near unexpected token `newline'\n", 51);
			return (1);
		}
	}
	write(STDERR_FILENO, "bash: syntax error near unexpected token `|'\n", 45);
	return (1);
}

int	check_pipe(char *str, int i)
{
	if (check_before_pipe(str, i))
		return (1);
	if (check_after_pipe(str, i))
		return (1);
	return (0);
}

int	check_for_syntax_errors(t_msh *ms)
{
	int	i;
	int	j;

	j = 0;
	i = -1;
	while (ms->line && ms->line[++i])
	{
		if (ms->line[i] == '|')
			j = check_pipe(ms->line, i);
		if (j != 0)
			return (1);
		if (ms->line[i] == '<' || ms->line[i] == '>')
			j = check_redirection(ms->line, i);
		if (j != 0)
			return (1);
	}
	return (0);
}

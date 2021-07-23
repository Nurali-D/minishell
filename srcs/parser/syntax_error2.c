#include "minishell.h"

int	check_after_redirection(char *str, int i)
{
	int	k;

	k = i;
	while (str[++k])
	{	if ((str[i] == '<' && str[i + 1] == '<') || (str[i] ==  '>' && str[i + 1] == '>'))
			k++;
		if (ft_isprint(str[k]) && (str[k] != ' '
				&& str[k] != '|' && str[k] != '<' && str[k] != '>'))
			return (0);
		else if (str[k] == '|')
		{
			write(STDERR_FILENO, "bash: syntax error near unexpected token `|'\n", 45);
			return (1);
		}
		else if (str[k] == '>' || str[k] == '<')
		{
			if (str[k] == '>' && str[k + 1] != '>')
				write(STDERR_FILENO, "bash: syntax error near unexpected token `>'\n", 45);
			else if (str[k] == '<' && str[k + 1] != '<')
				write(STDERR_FILENO, "bash: syntax error near unexpected token `<'\n", 45);
			else if (str[k] == '>' && str[k + 1] == '>')
				write(STDERR_FILENO, "bash: syntax error near unexpected token `>>'\n", 46);
			else if (str[k] == '<' && str[k + 1] == '<')
				write(STDERR_FILENO, "bash: syntax error near unexpected token `<<'\n", 46);
			return (1);
		}
	}
	write(STDERR_FILENO, "bash: syntax error near unexpected token `newline'\n", 51);
	return (1);
}

int	check_redirection(char *str, int i)
{
	if (check_after_redirection(str, i))
		return (1);
	return (0);
}

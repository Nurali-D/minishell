#include "minishell.h"

void	print_redirection_error(char *str, int k)
{
	if (str[k] == '>' && str[k + 1] != '>')
	{
		write(STDERR_FILENO, "bash: syntax error ", 19);
		write(STDERR_FILENO, "near unexpected token `>'\n", 26);
	}
	else if (str[k] == '<' && str[k + 1] != '<')
	{
		write(STDERR_FILENO, "bash: syntax error ", 19);
		write(STDERR_FILENO, "near unexpected token `<'\n", 26);
	}
	else if (str[k] == '>' && str[k + 1] == '>')
	{
		write(STDERR_FILENO, "bash: syntax error ", 19);
		write(STDERR_FILENO, "near unexpected token `>>'\n", 27);
	}
	else if (str[k] == '<' && str[k + 1] == '<')
	{
		write(STDERR_FILENO, "bash: syntax error ", 19);
		write(STDERR_FILENO, "near unexpected token `<<'\n", 27);
	}
}

int	check_after_redirection(char *str, int i, int k)
{
	k = i;
	while (str[++k])
	{
		if ((str[i] == '<' && str[i + 1] == '<')
			|| (str[i] == '>' && str[i + 1] == '>'))
			k++;
		if (ft_isprint(str[k]) && (str[k] != ' '
				&& str[k] != '|' && str[k] != '<' && str[k] != '>'))
			return (0);
		else if (str[k] == '|')
		{
			write(STDERR_FILENO, "bash: syntax error ", 19);
			write(STDERR_FILENO, "near unexpected token `|'\n", 26);
			return (1);
		}
		else if (str[k] == '>' || str[k] == '<')
		{
			print_redirection_error(str, k);
			return (1);
		}
	}
	write(STDERR_FILENO, "bash: syntax error ", 19);
	write(STDERR_FILENO, "near unexpected token `newline'\n", 32);
	return (1);
}

int	check_redirection(char *str, int i)
{
	int	k;

	k = 0;
	if (check_after_redirection(str, i, k))
		return (1);
	return (0);
}

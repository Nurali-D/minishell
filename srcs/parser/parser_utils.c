#include "minishell.h"

void	delete_quotes(char *str, int i, int j)
{
	if (i + 1 <= (int)ft_strlen(str))
		ft_memmove(&str[i], &str[i + 1], ft_strlen(&str[i + 1]) + 1);
	if (j + 1 <= (int)ft_strlen(str))
		ft_memmove(&str[j], &str[j + 1], ft_strlen(&str[j + 1]) + 1);
}

char	*treat_single_quotes(char *str, int *i)
{
	int		j;

	j = *i;
	while (str[++*i])
	{
		if (str[*i] == '|')
			str[*i] = (char)179;
		if (str[*i] == '\'')
			break ;
	}
	if (*i == (int)ft_strlen(str))
	{
		free(str);
		write(STDERR_FILENO, "Not interpret : ", 16);
		write(STDERR_FILENO, "unclosed single quotes\n", 23);
		return (NULL);
	}
	delete_quotes(str, *i, j);
	*i -= 2;
	return (str);
}

char	*treat_double_quotes(char *str, int *i, t_env *env)
{
	int		j;

	j = *i;
	while (str[++*i])
	{
		if (str[*i] == '|')
			str[*i] = (char)179;
		if (str[*i] == '\"')
			break ;
		if (str[*i] == '$')
		{
			str = treat_dollar(str, i, env);
			*i -= 1;
		}
	}
	if (*i == (int)ft_strlen(str))
	{
		free(str);
		write(STDERR_FILENO, "Not interpret : ", 16);
		write(STDERR_FILENO, "unclosed double quotes\n", 23);
		return (NULL);
	}
	delete_quotes(str, *i, j);
	*i -= 2;
	return (str);
}

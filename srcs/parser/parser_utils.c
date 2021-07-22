#include "minishell.h"

void	delete_quotes(char *str, int i, int j)
{
	ft_memmove(&str[i], &str[i + 1], ft_strlen(&str[i + 1]) + 1);
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
	delete_quotes(str, *i, j);
	printf("str = %s\n", str);
	*i -= 1;
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
			str = treat_dollar(str, i, env);
	}
	delete_quotes(str, *i, j);
	*i -= 1;
	return (str);
}

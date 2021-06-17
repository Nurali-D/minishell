#include "minishell.h"

static char	*delete_quotes(char *str, int i, int j)
{
	char	*before_quotes;
	char	*in_quotes;
	char	*after_quotes;
	char	*ret;
	char	*tmp;

	before_quotes = ft_substr(str, 0, j);
	in_quotes = ft_substr(str, j + 1, i -j - 1);
	after_quotes = ft_strdup(str + i + 1);
	ret = ft_strjoin(before_quotes, in_quotes);
	tmp = ret;
	ret = ft_strjoin(ret, after_quotes);
	free(tmp);
	free(before_quotes);
	free(in_quotes);
	free(after_quotes);
	return (ret);
}

char	*treat_single_quotes(char *str, int *i)
{
	int		j;
	char	*tmp;

	j = *i;
	while (str[++*i])
	{
		if (str[*i] == '\'')
			break;
	}
	tmp = str;
	str = delete_quotes(str, *i, j);
	*i -= 1;
	free(tmp);
	return (str);
}

char	*treat_slash(char *str, int *i)
{
	char	*before;
	char	*after;
	char	*ret;

	before = ft_substr(str, 0, *i);
	after = ft_strdup(str + *i + 1);
	ret = ft_strjoin(before, after);
	free(str);
	free(before);
	free(after);
	++(*i);
	return (ret);
}

char	*treat_double_quotes(char *str, int *i, t_env *env)
{
	int		j;
	char	*tmp;

	j = *i;
	while (str[++*i])
	{
		if (str[*i] == '\\' && (str[*i + 1] == '\"'
				|| str[*i + 1] == '$' || str[*i + 1] == '\\'))
			str = treat_slash(str, i);
		if (str[*i] == '\"')
			break;
		if (str[*i] == '$')
			str = treat_dollar(str, i, env);
	}
	tmp = str;
	str = delete_quotes(str, *i, j);
	*i -= 1;
	free(tmp);
	return (str);
}
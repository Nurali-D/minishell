#include "minishell.h"

static int	is_key(char c)
{
	if (c == '_' || ft_isalnum(c))
		return (1);
	return (0);
}

char	*is_key_in_env(char *key, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*replace_key(char *str, char *value, int *i, int j)
{
	char	*before;
	char	*after;
	char	*tmp;
	char	*tmp2;

	before = ft_substr(str, 0, j);
	after = ft_strdup(str + *i);
	tmp = ft_strjoin(before, value);
	*i = ft_strlen(tmp);
	tmp2 = tmp;
	if (after[0] != '\0')
	tmp = ft_strjoin(tmp, after);
	free(str);
	free(before);
	free(after);
	free(tmp2);
	return (tmp);
}

char	*treat_dollar(char *str, int *i, t_env *env)
{
	int		j;
	char	*tmp;
	char	*tmp2;

	j = *i;
	if (str[j + 1] == '?')
	{
		str = replace_question_mark(str, i);
		return (str);
	}
	while (str[++*i])
	{
		if (!is_key(str[*i]))
			break;
	}
	if (*i == j + 1)
		return (str);
	tmp = ft_substr(str, j + 1, *i - j - 1);
	tmp2 = is_key_in_env(tmp, env);
	
	if (tmp2 != NULL)
		str = replace_key(str, tmp2, i, j);
	else if (str[j + 1] != ' ')
	{
		ft_memmove(&str[j], &str[*i], ft_strlen(&str[*i]) + 1);
		*i = j - 1;
	}
	free(tmp);
	return (str);
}

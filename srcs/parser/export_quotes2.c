#include "minishell.h"

int	ft_nwords(char *str, char d)
{
	size_t	i;
	int		n;

	i = 0;
	n = 0;
	while (str[i])
	{
		while (str[i] == d)
			i++;
		if (str[i] != '\0')
			n++;
		while (str[i] && str[i] != d)
			i++;
	}
	return (n);
}

char	*get_in_quotes2(char *export, int *i, int j)
{
	char	**splitted;
	char	instead[2];
	char	*ret;
	char	*tmp;

	ret = NULL;
	instead[0] = (char)175;
	instead[1] = '\0';
	splitted = ft_split(&export[*i + 1], ' ');
	ret = ft_strdup(splitted[0]);
	j = 0;
	while (splitted[++j])
	{
		tmp = ret;
		ret = ft_strjoin(ret, instead);
		if (tmp)
			free(tmp);
		tmp = ret;
		ret = ft_strjoin(ret, splitted[j]);
		free(tmp);
	}
	free_array(splitted);
	return (ret);
}

char	*get_in_quotes(char *export, int *i, char c)
{
	int		j;
	int		k;
	char	*ret;

	ret = NULL;
	k = 0;
	j = *i + 1;
	while (export[j])
	{
		if (export[j] == c)
		{
			k = j;
			break ;
		}
		j++;
	}
	if (k == 0)
		return (NULL);
	export[k] = '\0';
	if (ft_nwords(&export[*i + 1], ' ') > 1)
		ret = get_in_quotes2(export, i, j);
	export[k] = c;
	*i = k;
	return (ret);
}

int	find_pipe(char *export, int i)
{
	int	pipe;

	pipe = 0;
	while (export[++i])
	{
		if (export[i] == '|')
		{
			pipe = i;
			break ;
		}
	}
	return (pipe);
}

int	check_before_export(char *str, char *export)
{
	int		i;
	int		dif;

	dif = (int)(export - str);
	i = dif;
	if (i > 0)
	{
		while (i > 0 && str[--i])
		{
			if (ft_isprint(str[i]) && str[i] != ' '
				&& str[i] != '\'' && str[i] != '"' && str[i] != '|')
				return (1);
			if (str[i] == '|')
				break ;
		}
	}
	return (0);
}

#include "minishell.h"

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

char	*get_in_quotes(char *export, int *i, char c)
{
	int		j;
	int		k;
	char	*ret;
	char	**splitted;
	char	instead[2];

	instead[0] = 175;
	instead[1] = '\0';
	ret = NULL;
	k = 0;
	j = *i + 1; // start quotes + 1
	while (export[j])
	{
		if (export[j] == c)
		{
			k = j; // end quotes
			break ;
		}
		j++;
	}
	if (k == 0)
		return (NULL);
	export[k] = '\0';
	if (ft_nwords(&export[*i + 1], ' ') > 1)
	{
		splitted = ft_split(&export[*i + 1], ' ');
		ret = ft_strdup(splitted[0]);
		j = 0;
		while (splitted[++j])
		{
			ret = ft_strjoin(ret, instead);
			ret = ft_strjoin(ret, splitted[j]);
		}
	}
	export[k] = c;
	*i = k;
	return (ret);
}

void	check_after_export(char *export, char **str)
{
	int		i;
	int		start;
	int		pipe;
	char	*ret;
	char	*before;
	char	*after;
	char	*tmp;

	pipe = 0;
	i = 5;
	ret = NULL;
	while (export[++i])
	{
		if (export[i] == '|')
		{
			pipe = i;
			break ;
		}
	}
	if (pipe != 0)
		export[pipe] = '\0';
	i = 5;
	while (export[++i])
	{
		if (export[i] == '\'' || export[i] == '"')
		{
			start = i;
			ret = get_in_quotes(export, &i, export[i]);
			if (ret == NULL)
				return ;
			before = ft_substr(str, 0, (int)(export - str) + start);
			after = ft_substr(str, (int)(export - str) + i, ft_strlen(&export[i]));
			tmp = ft_strjoin(before, ret);
			tmp = ft_strjoin(tmp, after);
			
		}
	}
}

void	check_export_quotes(char **str)
{
	char	*export;
	
	
	export = ft_strnstr(*str, "export", ft_strlen(*str));
	if (export == NULL || ft_strlen(export) == 6 || check_before_export(*str, export) != 0)
		return ;
	check_after_export(export, str);
}
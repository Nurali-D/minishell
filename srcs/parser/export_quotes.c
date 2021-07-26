#include "minishell.h"

void	free_ex(t_exp *ex)
{
	free(ex->before);
	free(ex->after);
	free(ex->ret);
	free(ex->tmp1);
	free(ex->tmp2);
}

int	treat_quotes_export(t_exp *ex, int *i)
{
	ex->start = *i;
	ex->ret = get_in_quotes(ex->export, i, ex->export[*i]);
	if (ex->ret == NULL)
	{
		if (ex->pipe != 0)
			ex->export[ex->pipe] = '|';
		return (-1);
	}
	ex->before = ft_substr(*ex->str, 0,
			(int)(ex->export - *ex->str) + ex->start + 1);
	if (ex->pipe != 0)
		ex->export[ex->pipe] = '|';
	ex->after = ft_substr(*ex->str, (int)(ex->export - *ex->str) + *i,
			ft_strlen(&ex->export[*i]));
	ex->tmp1 = ft_strjoin(ex->before, ex->ret);
	ex->tmp2 = *ex->str;
	*ex->str = ft_strjoin(ex->tmp1, ex->after);
	*i = ex->start + ft_strlen(ex->ret) + 1;
	free_ex(ex);
	ex->export = ft_strnstr(*ex->str, "export", ft_strlen(*ex->str));
	ex->pipe = find_pipe(ex->export, 5);
	if (ex->pipe != 0)
		ex->export[ex->pipe] = '\0';
	return (0);
}

void	check_after_export(char *export, char **str)
{
	t_exp	ex;
	int		i;

	i = 5;
	ex.export = export;
	ex.str = str;
	ex.pipe = find_pipe(ex.export, i);
	ex.ret = NULL;
	if (ex.pipe != 0)
		ex.export[ex.pipe] = '\0';
	while (export[++i])
	{
		if (ex.export[i] == '\'' || ex.export[i] == '"')
			if (treat_quotes_export(&ex, &i) == -1)
				return ;
	}
	if (ex.pipe != 0)
		ex.export[ex.pipe] = '|';
}

void	check_export_quotes(char **str)
{
	char	*export;

	export = ft_strnstr(*str, "export", ft_strlen(*str));
	if (export == NULL || ft_strlen(export) == 6
		|| check_before_export(*str, export) != 0)
		return ;
	check_after_export(export, str);
}

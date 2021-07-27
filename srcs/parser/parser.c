#include "minishell.h"

void	add_command_to_tokens(t_msh *ms, char *str)
{
	t_token	*tmp;

	tmp = (t_token *)malloc(sizeof(t_token));
	tmp->next = NULL;
	tmp->fd_err = 0;
	tmp->fd_in = -1;
	tmp->fd_out = -1;
	tmp->args = get_args_fd(str, tmp);
	put_to_tokens_list(ms, tmp);
}

void	change_179(char **s)
{
	int	i;
	int	j;

	i = -1;
	while (s[++i])
	{
		j = -1;
		while (s[i][++j])
		{
			if (s[i][j] == (char)179)
				s[i][j] = '|';
		}
	}
}

void	make_tokens(t_msh *ms)
{
	char	**splitted;
	int		i;

	splitted = NULL;
	splitted = ft_split(ms->line, '|');
	change_179(splitted);
	i = -1;
	while (splitted[++i])
	{
		add_command_to_tokens(ms, splitted[i]);
		free(splitted[i]);
	}
	free(splitted);
}

int	parse_line(t_msh *ms)
{
	int	i;

	i = -1;
	while (ms->line && ms->line[++i])
	{
		if (ms->line[i] == '\'')
			ms->line = treat_single_quotes(ms->line, &i);
		else if (ms->line[i] == '"')
			ms->line = treat_double_quotes(ms->line, &i, ms->env_list);
		else if (ms->line[i] == '$')
			ms->line = treat_dollar(ms->line, &i, ms->env_list);
	}
	if (ms->line == NULL || check_for_syntax_errors(ms))
	{
		g_status = 258;
		return (1);
	}
	make_tokens(ms);
	replace_175(ms->tokens);
	return (0);
}

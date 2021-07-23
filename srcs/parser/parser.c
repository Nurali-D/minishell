#include "minishell.h"

void	add_command_to_tokens(t_msh *ms, char *str)
{
	t_token	*tmp;

	tmp = (t_token *)malloc(sizeof(t_token));
	tmp->type = COMMAND;
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
	while(s[++i])
	{
		j = -1;
		while (s[i][++j])
		{
			if (s[i][j] == (char)179)
				s[i][j] = '|';
		}
	}
	printf("s = %s\n", *s);
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
	// if (check_for_syntax_errors(ms))
	// 	return (1);
	while (ms->line && ms->line[++i])
	{
		if (ms->line[i] == '\'')
			ms->line = treat_single_quotes(ms->line, &i);
		else if (ms->line[i] == '"')
			ms->line = treat_double_quotes(ms->line, &i, ms->env_list);
		else if (ms->line[i] == '$')
			ms->line = treat_dollar(ms->line, &i, ms->env_list);
	}
	make_tokens(ms);
	t_token *tmp = ms->tokens;//
	while (tmp)//
	{
		printf("token %d\n", tmp->type); //
		if (tmp->args)//
		{
			for (int k = 0; tmp->args[k]; k++)//
				printf("args[%d] = %s\n", k, tmp->args[k]);//
			printf("fd_err = %d, fd_in = %d, fd_out = %d\n", tmp->fd_err, tmp->fd_in, tmp->fd_out);//

		}
		tmp = tmp->next;//
	}
	printf("%s /%zu\n", ms->line, ft_strlen(ms->line));//

	return (0);//
}

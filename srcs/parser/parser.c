#include "minishell.h"

// void	treat_semicolon(t_msh *ms)
// {

// }

char	**get_args(char *line, int i)
{
	int		j;
	int		k;
	char	*tmp;
	char	**temp;

	k = i;
	j = -1;
	while (++j < i)
		if (ft_isprint(line[j]) && line[j] != ' ')
			break ;
	while (--k > 0)
		if (ft_isprint(line[k]) && line[k] != ' ')
			break ;
	tmp = (char *)malloc(sizeof(char) * (k - j + 2));
	ft_strlcpy(tmp, &line[j], k - j + 2);
	// printf("tmp = /%s/\n", tmp);
	temp = ft_split(tmp, ' ');
	// k = -1;
	// while (temp[++k])
	// 	printf("%d = /%s/\n", k, temp[k]);
	return (temp);
}

void	put_to_tokens_list(t_msh *ms, t_token *new)
{
	t_token	*tmp;

	tmp = ms->tokens;
	while (tmp)
	{
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	if (tmp)
		tmp->next = new;
	else
		ms->tokens = new;
}

void	treat_pipe(t_msh *ms, int i, int j)
{
	t_token *tmp;
	// int		k;

	tmp = (t_token *)malloc(sizeof(t_token));
	tmp->type = COMMAND;
	tmp->next = NULL;
	tmp->args = get_args(&ms->line[j], i - j);
	put_to_tokens_list(ms, tmp);
	tmp = (t_token *)malloc(sizeof(t_token));
	tmp->type = PIPE;
	tmp->next = NULL;
	tmp->args = NULL;
	put_to_tokens_list(ms, tmp);
	// tmp = ms->tokens;
	// while (tmp)
	// {
	// 	printf("token %d\n", tmp->type);
	// 	if (tmp->args)
	// 	{
	// 		for (int k = 0; tmp->args[k]; k++)
	// 			printf("args[%d] = %s\n", k, tmp->args[k]);
	// 	}
	// 	tmp = tmp->next;
	// }
}

// void	treat_redirection(t_msh *ms)
// {

// }

void	add_command_to_tokens(t_msh *ms, int j, int i)
{
	t_token	*tmp;

	tmp = (t_token *)malloc(sizeof(t_token));
	tmp->type = COMMAND;
	tmp->next = NULL;
	tmp->args = get_args(&ms->line[j], i - j);
	put_to_tokens_list(ms, tmp);
}

void	parse_line(t_msh *ms)
{
	int	i = -1;
	int	j = 0;

	// check_for_syntax_errors(ms);
	while (ms->line && ms->line[++i])
	{
		if (ms->line[i] == '\'')
			ms->line = treat_single_quotes(ms->line, &i);
		else if (ms->line[i] == '\\')
			ms->line = treat_slash(ms->line, &i);
		else if (ms->line[i] == '"')
			ms->line = treat_double_quotes(ms->line, &i, ms->env_list);
		else if (ms->line[i] == '$')
			ms->line = treat_dollar(ms->line, &i, ms->env_list);
		// else if (ms->line[i] == ';')
		// 	treat_semicolon(ms);
		else if (ms->line[i] == '|')
		{
			treat_pipe(ms, i, j);
			j = i + 1;
		}
		// else if (ms->line[i] == ">" || ms->line[i] == "<")
		// {
		// 	treat_redirection(ms);
		// 	j = i + 1;
		// }
	}
	add_command_to_tokens(ms, j, i);
	// t_token *tmp = ms->tokens;
	// while (tmp)
	// {
	// 	printf("token %d\n", tmp->type);
	// 	if (tmp->args)
	// 	{
	// 		for (int k = 0; tmp->args[k]; k++)
	// 			printf("args[%d] = %s\n", k, tmp->args[k]);
	// 	}
	// 	tmp = tmp->next;
	// }
	// printf("%s\n", ms->line);
}

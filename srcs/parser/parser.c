#include "minishell.h"

void	add_command_to_tokens(t_msh *ms, int j, int i)
{
	t_token	*tmp;

	tmp = (t_token *)malloc(sizeof(t_token));
	tmp->type = COMMAND;
	tmp->next = NULL;
	tmp->args = get_args(&ms->line[j], i - j);
	put_to_tokens_list(ms, tmp);
}

int	parse_line(t_msh *ms)
{
	int	i = -1;
	int	j = 0;

	if (check_for_syntax_errors(ms))
		return (1);
	while (ms->line && ms->line[++i])
	{
		if (ms->line[i] == '\'')
			ms->line = treat_single_quotes(ms->line, &i);
		// else if (ms->line[i] == '\\')
		// 	ms->line = treat_slash(ms->line, &i);
		else if (ms->line[i] == '"')
			ms->line = treat_double_quotes(ms->line, &i, ms->env_list);
		else if (ms->line[i] == '$')
			ms->line = treat_dollar(ms->line, &i, ms->env_list);
		else if (ms->line[i] == '|')
		{
			treat_separator(ms, i, j, PIPE);
			j = i + 1;
		}
		else if (ms->line[i] == '>' || ms->line[i] == '<')
		{
			treat_redirections(ms, &i, j);
			j = i + 1;
		}
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
	return (0);
}

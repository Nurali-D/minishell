#include "minishell.h"

// void	redirect_stand_output(t_msh *ms, int i, int j)
// {
// 	t_token	*tmp;

// 	tmp = (t_token *)malloc(sizeof(t_token));
// 	tmp->type = COMMAND;
// 	tmp->next = NULL;
// 	tmp->args = get_args(&ms->line[j], i - j);
// 	put_to_tokens_list(ms, tmp);
// 	tmp = (t_token *)malloc(sizeof(t_token));
// 	tmp->type = REDIRECT_ST_OUTPUT;
// 	tmp->next = NULL;
// 	tmp->args = NULL;
// 	put_to_tokens_list(ms, tmp);
// }

// void	append_stand_output(t_msh *ms, int i, int j)
// {
// 	t_token	*tmp;

// 	tmp = (t_token *)malloc(sizeof(t_token));
// 	tmp->type = COMMAND;
// 	tmp->next = NULL;
// 	tmp->args = get_args(&ms->line[j], i - j);
// 	put_to_tokens_list(ms, tmp);
// 	tmp = (t_token *)malloc(sizeof(t_token));
// 	tmp->type = APPEND;
// 	tmp->next = NULL;
// 	tmp->args = NULL;
// 	put_to_tokens_list(ms, tmp);
// }

void	treat_redirections(t_msh *ms, int *i, int j)
{
	if (ms->line[*i] == '>' && ms->line[*i + 1] != '>')
		treat_separator(ms, *i, j, REDIRECT_ST_OUTPUT);
	else if (ms->line[*i] == '>' && ms->line[*i + 1] == '>')
	{
		treat_separator(ms, *i, j, APPEND);
		*i += 1;
	}
	else if (ms->line[*i] == '<' && ms->line[*i + 1] != '<')
		treat_separator(ms, *i, j, REDIRECT_ST_INPUT);
	else if (ms->line[*i] == '<' && ms->line[*i + 1] == '<')
	{
		treat_separator(ms, *i, j, HEREDOC);
		*i += 1;
	}
}

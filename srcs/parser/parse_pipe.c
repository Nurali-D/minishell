#include "minishell.h"

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

void	treat_separator(t_msh *ms, int i, int j, int type)
{
	t_token *tmp;

	tmp = (t_token *)malloc(sizeof(t_token));
	tmp->type = COMMAND;
	tmp->next = NULL;
	tmp->args = get_args(&ms->line[j], i - j);
	put_to_tokens_list(ms, tmp);
	tmp = (t_token *)malloc(sizeof(t_token));
	tmp->type = type;
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

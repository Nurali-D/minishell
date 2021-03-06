#include "minishell.h"

static t_env	*get_new_list_element(t_env *new, t_env *head)
{
	t_env	*temp;

	temp = head;
	while (temp)
	{
		if (!(temp->next))
			break ;
		temp = temp->next;
	}
	if (!(head))
		head = new;
	else
		temp->next = new;
	return (head);
}

void	get_env_list(char **env, t_msh *ms)
{
	int		i;
	int		j;
	char	**splitted;
	t_env	*temp;

	i = -1;
	while (env[++i])
	{
		temp = (t_env *)malloc(sizeof(t_env));
		temp->next = NULL;
		temp->value = NULL;
		splitted = ft_split(env[i], '=');
		temp->key = ft_strdup(splitted[0]);
		if (splitted[1])
			temp->value = ft_strdup(splitted[1]);
		ms->env_list = get_new_list_element(temp, ms->env_list);
		j = -1;
		while (splitted[++j])
			free(splitted[j]);
		free(splitted);
	}
}

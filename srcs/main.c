#include "minishell.h"

t_env	*get_new_list_element(t_env *new, t_env *head)
{
	t_env	*temp;

	temp = head;
	while (temp)
	{
		if (!(temp->next))
			break;
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
	char	**splitted;
	int		i;
	t_env	*temp;

	i = 0;
	while (env[i])
	{
		temp = (t_env *)malloc(sizeof(t_env));
		// if (!temp)
		// 	error_free(ms);
		temp->next = NULL;
		splitted = ft_split(env[i], '=');
		temp->var = splitted[0];
		temp->var_value = splitted[1];
		ms->env_list = get_new_list_element(temp, ms->env_list);
		i++;
	}
}

void	init_ms(t_msh *ms)
{
	ms->env_list = NULL;
	ms->tokens = NULL;
}

int	main(int argc, char **argv, char **env)
{
	t_msh	ms;
	t_env	*temp;
	char	buf[200];

	init_ms(&ms);
	get_env_list(env, &ms);
	temp = ms.env_list;
	while (temp)
	{
		printf("%s=%s\n", temp->var, temp->var_value);
		temp = temp->next;
	}
	// while (1)
	// {
	// 	write(1, "my-shell$", 9);
	// 	read(0, buf, 200);

	// }
	return (0);
}

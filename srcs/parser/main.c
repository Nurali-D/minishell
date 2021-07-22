#include "minishell.h"

void	init_ms(t_msh *ms)
{
	ms->env_list = NULL;
	ms->tokens = NULL;
	ms->line = NULL;
	ms->prompt = "➜  minishell$ ";
}

void	free_env(t_msh *ms)
{
	t_env	*tmp;
	t_env	*tmp2;

	tmp = ms->env_list;
	while (tmp)
	{
		free(tmp->key);
		if (tmp->value != NULL)
			free(tmp->value);
		tmp2 = tmp;
		tmp = tmp->next;
		free(tmp2);
	}
	if (tmp)
		free(tmp);
}

int	main(int argc, char **argv, char **env)
{
	t_msh	ms;

	(void)argc;
	(void)argv;
	g_status = 123; //testing $?
	init_ms(&ms);
	get_env_list(env, &ms);
	// get_env_arr(&ms);
	parse_execute(&ms);
	free_env(&ms);
	return (0);
}

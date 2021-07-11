#include "minishell.h"

void	init_ms(t_msh *ms)
{
	ms->env_list = NULL;
	ms->tokens = NULL;
	ms->line = NULL;
	ms->prompt = "➜  minishell$ ";
}

int	main(int argc, char **argv, char **env)
{
	t_msh	ms;

	(void)argc;
	(void)argv;
	init_ms(&ms);
	get_env_list(env, &ms);
	// get_env_arr(&ms);
	parse_execute(&ms);
	return (0);
}

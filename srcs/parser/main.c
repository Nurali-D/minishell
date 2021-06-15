#include "minishell.h"

void	init_ms(t_msh *ms)
{
	ms->env_list = NULL;
	ms->tokens = NULL;
	ms->line = NULL;
	ms->prompt = "\e[32mminishell$\e[0m ";
}

int	main(int argc, char **argv, char **env)
{
	t_msh	ms;

	(void)argc;
	(void)argv;
	init_ms(&ms);
	get_env_list(env, &ms);
	parse_execute(&ms);
	return (0);
}

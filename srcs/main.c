#include "minishell.h"

void	init_ms(t_msh *ms)
{
	ms->env_list = NULL;
	ms->tokens = NULL;
	ms->line = (char *)malloc(sizeof(char));
	ft_bzero(ms->line, 1);
	ms->buf = (char *)malloc(sizeof(char) * 10);
	ms->term_name = "xterm-256color";
	ms->tmp = NULL;
}

int	main(int argc, char **argv, char **env)
{
	t_msh	ms;

	init_ms(&ms);
	get_env_list(env, &ms);
	parse_execute(&ms);

	return (0);
}

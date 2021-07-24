#include "minishell.h"

void	sig_handler(int handler)
{
	(void)handler;
	rl_replace_line("➜  minishell$ ", 0);
	rl_redisplay();
	rl_on_new_line();
	ft_putendl_fd("\b\b", 1);
}

void	quit_handler(int handler)
{
	(void)handler;
}

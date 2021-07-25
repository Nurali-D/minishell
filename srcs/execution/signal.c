#include "minishell.h"

void	sig_handler(int handler)
{
	(void)handler;
	rl_on_new_line();
	rl_redisplay();
	ft_putstr_fd("  \b\b\n", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

void	quit_handler(int handler)
{
	(void)handler;
}

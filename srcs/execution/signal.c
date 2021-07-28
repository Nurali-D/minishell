#include "minishell.h"

void	get_status(int status)
{
	if ((WIFEXITED(status)) != 0)
	{
		g_status = (WEXITSTATUS(status));
	}
	else if ((WIFSIGNALED(status)) != 0)
	{
		printf("sig = %d\n", WTERMSIG(status));
		if ((WTERMSIG(status)) == 3)
		{
			g_status = (131);
			ft_putendl_fd("Quit: 3", 1);
		}
		else if ((WTERMSIG(status)) == 2)
		{
			ft_putchar_fd('\n', 1);
			g_status = (130);
		}
	}
}

void	ctrl_c_handler(int handler)
{
	(void)handler;
	rl_on_new_line();
	rl_redisplay();
	ft_putstr_fd("  \b\b\n", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
	g_status = 1;
}

void	ctrl_d_handler(int handler)
{
	(void)handler;
	ft_putstr_fd("\033[A\r", 2);
	ft_putstr_fd("➜  minishell$ exit\n", 2);
	exit(g_status);
}

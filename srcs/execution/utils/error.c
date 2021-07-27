#include "minishell.h"

void	ft_error(char *s1, char *s2, char *err, int status)
{
	ft_putstr_fd("\e[0;91m➜\e[0m  minishell: ", 2);
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(": ", 2);
	if (s2)
	{
		ft_putstr_fd(s2, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(err, 2);
	ft_putchar_fd('\n', 2);
	g_status = status;
}

void	env_error(char *s1, char *s2, char *err, int status)
{
	ft_putstr_fd("\e[0;91m➜\e[0m  minishell: ", 2);
	ft_putstr_fd(s1, 2);
	ft_putchar_fd('`', 2);
	ft_putstr_fd(s2, 2);
	ft_putchar_fd('\'', 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(err, 2);
	ft_putchar_fd('\n', 2);
	g_status = status;
}

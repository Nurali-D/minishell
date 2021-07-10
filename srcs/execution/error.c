#include "minishell.h"

void	ft_error(char *cmd, char *arg, int err)
{
	ft_putstr_fd("\e[0;91m➜\e[0m  minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	if (arg)
	{
		if (err == -2)
			ft_putchar_fd('`', 2);
		ft_putstr_fd(arg, 2);
		if (err == -2)
			ft_putchar_fd('\'', 2);
		ft_putstr_fd(": ", 2);
	}
	if (err == -1)
		ft_putstr_fd(": command not found", 2);
	else if (err == -2)
		ft_putstr_fd("not a valid identifier", 2);
	else
		ft_putstr_fd(strerror(err), 2);
	ft_putchar_fd('\n', 2);
}

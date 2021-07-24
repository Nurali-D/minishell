#include "minishell.h"

void	ft_error(char *cmd, char *arg, char *err, int flag)
{
	ft_putstr_fd("\e[0;91m➜\e[0m  minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	if (arg)
	{
		if (flag == 2)
			ft_putchar_fd('`', 2);
		ft_putstr_fd(arg, 2);
		if (flag == 2)
			ft_putchar_fd('\'', 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(err, 2);
	ft_putchar_fd('\n', 2);
}

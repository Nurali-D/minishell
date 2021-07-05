#include "minishell.h"

void	cd_error(char *command, char *arg, int type)
{
	ft_putstr_fd("\e[0;91m➜\e[0m  minishell: ", 1);
	ft_putstr_fd(command, 1);
	ft_putstr_fd(arg, 1);
	ft_putstr_fd(": ", 1);
	ft_putstr_fd(strerror(type), 1);
	ft_putchar_fd('\n', 1);
}

// void	cmd_not_found()
// {
	
// }

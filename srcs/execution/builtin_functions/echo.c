#include "minishell.h"

void	echo_execution(char **args)
{
	int	i;

	i = 1;
	g_status = 0;
	while (args[i] && (ft_strcmp(args[i], "-n")) == 0)
		i++;
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[++i])
			ft_putchar_fd(' ', 1);
	}
	if (!(args[1]) || (ft_strcmp(args[1], "-n")) != 0)
		ft_putchar_fd('\n', 1);
}

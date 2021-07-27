#include "minishell.h"

void	pwd_execution(void)
{
	char	*path;

	g_status = 0;
	path = NULL;
	path = getcwd(NULL, 0);
	ft_putendl_fd(path, 1);
	free(path);
	path = NULL;
}

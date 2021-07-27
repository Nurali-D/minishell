#include "minishell.h"

void	free_array(char **array)
{
	int		i;

	i = 0;
	while (array && array[i])
	{
		free(array[i]);
		i++;
	}
	free(array[i]);
	free(array);
}

void	free_fd_pid(int **fd, int *pid, t_msh *ms)
{
	int	i;

	i = -1;
	while (++i < ms->nc + 1)
	{
		if (fd && fd[i])
			free(fd[i]);
	}
	if (fd)
		free(fd);
	if (pid)
		free(pid);
	free_tokens(ms->tokens);
	ms->tokens = NULL;
}

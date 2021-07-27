#include "minishell.h"

int	close_fd(int **fd, int n)
{
	int	j;

	j = -1;
	while (++j < n)
	{
		close(fd[j][0]);
		close(fd[j][1]);
	}
	return (0);
}

int	make_forks(t_msh *ms, int **fd, int *pid, int status)
{
	int		i;
	t_token	*tmp;

	tmp = ms->tokens;
	i = 0;
	while (tmp)
	{
		pid[i] = fork();
		if (pid[i] < 0)
			return (-1);
		else if (pid[i] == 0)
		{
			ms->i = i;
			if (exec_command(fd, tmp, ms, pid) == -1)
				return (-1);
		}
		tmp = tmp->next;
		i++;
	}
	close_fd(fd, ms->nc + 1);
	i = -1;
	while (++i < ms->nc)
		waitpid(pid[i], &status, WUNTRACED);
	get_status(status);
	return (0);
}

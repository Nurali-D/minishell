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

void	make_forks2(int *pid, int nc)
{
	int	i;
	int	status;
	int	temp_status;

	i = -1;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	while (++i < nc)
	{
		waitpid(pid[i], &status, WUNTRACED);
		if ((WIFEXITED(status)) != 0)
			get_status(status);
		else
			temp_status = status;
	}
	if (temp_status != 0)
		get_status(temp_status);
}

int	make_forks(t_msh *ms, int **fd, int *pid)
{
	int		i;
	t_token	*tmp;

	i = 0;
	tmp = ms->tokens;
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
	make_forks2(pid, ms->nc);
	return (0);
}

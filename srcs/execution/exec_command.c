#include "minishell.h"

void	first_command(t_token *token, int **fd)
{
	if (token->fd_in != -1)
	{
		dup2(token->fd_in, STDIN_FILENO);
		close(token->fd_in);
	}
	if (token->fd_out != -1)
	{
		dup2(token->fd_out, STDOUT_FILENO);
		close(token->fd_out);
	}
	else
		dup2((fd[1][1]), STDOUT_FILENO);
}

void	last_command(t_token *token, int **fd, t_msh *ms)
{
	if (token->fd_in != -1)
	{
		dup2(token->fd_in, STDIN_FILENO);
		close(token->fd_in);
	}
	else
		dup2(fd[ms->i][0], STDIN_FILENO);
	if (token->fd_out != -1)
	{
		dup2(token->fd_out, STDOUT_FILENO);
		close(token->fd_out);
	}
}

void	other_command(t_token *token, int **fd, t_msh *ms)
{
	if (token->fd_in != -1)
	{
		dup2(token->fd_in, STDIN_FILENO);
		close(token->fd_in);
	}
	else
		dup2(fd[ms->i][0], STDIN_FILENO);
	if (token->fd_out != -1)
	{
		dup2(token->fd_out, STDOUT_FILENO);
		close(token->fd_out);
	}
	else
		dup2(fd[ms->i + 1][1], STDOUT_FILENO);
}

int	exec_command(int **fd, t_token *token, t_msh *ms, int *pid)
{
	(void)pid;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (token->fd_err == -1)
	{
		close_fd(fd, ms->nc + 1);
		exit (-1);
	}
	if (ms->i == 0)
		first_command(token, fd);
	else if (token->next == NULL)
		last_command(token, fd, ms);
	else
		other_command(token, fd, ms);
	close_fd(fd, ms->nc + 1);
	check_functions(token, ms->env_list, ms->nc);
	free_fd_pid(fd, pid, ms);
	free_env(ms);
	exit (0);
}

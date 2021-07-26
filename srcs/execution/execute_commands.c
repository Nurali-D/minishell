#include "minishell.h"

int	count_tokens(t_token *tokens)
{
	t_token	*tmp;
	int		i;

	tmp = tokens;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

int	execute_one_command(t_msh *ms)
{
	int	saved_stdout;
	int	saved_stdin;

	if (ms->tokens->fd_in != -1)
	{
		saved_stdin = dup(STDIN_FILENO);
		dup2(ms->tokens->fd_in, STDIN_FILENO);
		close(ms->tokens->fd_in);
	}
	if (ms->tokens->fd_out != -1)
	{
		saved_stdout = dup(STDOUT_FILENO);
		dup2(ms->tokens->fd_out, STDOUT_FILENO);
		close(ms->tokens->fd_out);
	}
	check_functions(ms->tokens, ms->env_list);
	if (ms->tokens->fd_in != -1)
	{
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
	}
	if (ms->tokens->fd_out != -1)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
	return (0);
}

void	execute_commands(t_msh *ms)
{
	int		**fd;
	int		*pid;
	int		i;

	ms->nc = count_tokens(ms->tokens);
	fd = NULL;
	pid = NULL;
	if (ms->nc > 1)
	{
		fd = (int **)malloc(sizeof(int *) * (ms->nc + 1));
		i = -1;
		while (++i < ms->nc + 1)
			fd[i] = (int *)malloc(sizeof(int) * 2);
		pid = (int *)malloc(sizeof(int) * ms->nc);
		i = -1;
		while (++i < ms->nc + 1)
			pipe(fd[i]);
		make_forks(ms, fd, pid);
		// free_fd_pid();
	}
	else
	{
		if (ms->tokens->fd_err == -1)
			return ;
		execute_one_command(ms);
	}
	unlink("heredoc_temp");
}
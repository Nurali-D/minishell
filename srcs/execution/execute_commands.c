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

void	treat_fd(t_token *token, int *s_in, int *s_out)
{
	if (token->fd_in != -1)
	{
		*s_in = dup(STDIN_FILENO);
		dup2(token->fd_in, STDIN_FILENO);
		close(token->fd_in);
	}
	if (token->fd_out != -1)
	{
		*s_out = dup(STDOUT_FILENO);
		dup2(token->fd_out, STDOUT_FILENO);
		close(token->fd_out);
	}
}

int	execute_one_command(t_msh *ms)
{
	int	saved_stdout;
	int	saved_stdin;

	treat_fd(ms->tokens, &saved_stdin, &saved_stdout);
	check_functions(ms->tokens, ms->env_list, ms->nc);
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

void	execute_commands2(t_msh *ms)
{
	int		**fd;
	int		*pid;
	int		i;

	fd = NULL;
	pid = NULL;
	fd = (int **)malloc(sizeof(int *) * (ms->nc + 1));
	i = -1;
	while (++i < ms->nc + 1)
		fd[i] = (int *)malloc(sizeof(int) * 2);
	pid = (int *)malloc(sizeof(int) * ms->nc);
	i = -1;
	while (++i < ms->nc + 1)
		pipe(fd[i]);
	make_forks(ms, fd, pid, 0);
	free_fd_pid(fd, pid, ms);
}

void	execute_commands(t_msh *ms)
{
	ms->nc = count_tokens(ms->tokens);
	if (ms->nc > 1)
		execute_commands2(ms);
	else
	{
		if (ms->tokens->fd_err == -1)
			return ;
		execute_one_command(ms);
	}
	unlink("heredoc_temp");
}

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/errno.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../lib/libft/libft.h"

int	g_status;
// g_status

void	rl_replace_line(const char *text, int clear_undo);

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_token
{
	char			**args;
	int				fd_in;
	int				fd_out;
	int				fd_err;
	struct s_token	*next;
}					t_token;

typedef struct s_msh
{
	t_token		*tokens;
	t_env		*env_list;
	char		*prompt;
	char		*line;
	char		**env;
	int			nc;
	int			i;
}				t_msh;

/*
** Pars functions
*/
void	get_env_list(char **env, t_msh *ms);
void	parse_execute(t_msh *ms);
int		parse_line(t_msh *ms);
int		check_for_syntax_errors(t_msh *ms);
void	error_function(t_msh *ms, char *error);
char	*treat_single_quotes(char *str, int *i);
char	*treat_double_quotes(char *str, int *i, t_env *env);
char	*treat_dollar(char *str, int *i, t_env *env);
char	**get_args_fd(char *str, t_token *token);
void	put_to_tokens_list(t_msh *ms, t_token *new);
void	treat_redirections(t_msh *ms, int *i, int j);
int		check_single_quotes(char *line, int *i);
int		check_double_quotes(char *line, int *i);
char	*replace_question_mark(char *str, int *i);
void	find_redirections(char **str, t_token *token, char c);
int		find_last_redirection(char *str, char c);
void	cut_redirection_from_str(char **names, char **str, int i);
void	save_fdin_to_token(char **filenames, char **heredoc_limiters,
			t_token *token, int last);
void	read_from_heredoc(char **hrd_lim);
char	*check_infiles(char **filenames);
int		file_exist(char *filename);
void	save_fdout_to_token(char **filenames, char **append,
			t_token *token, int last);
void	free_array(char **array);
int		check_redirection(char *str, int i);
void	replace_extended_ascii(t_token *tokens);
void	free_tokens(t_token *tokens);
void	free_env(t_msh *ms);
void	free_fd_pid(int **fd, int *pid, t_msh *ms);

/*
** Exec functions
*/
int		check_execve_functions(char **args, t_env *head);
void	check_fullpath_functions(char **args, t_env *head);
void	check_functions(t_token *token, t_env *env_list);
void	execute_commands(t_msh *ms);
int		close_fd(int **fd, int n);
int		make_forks(t_msh *ms, int **fd, int *pid);
int		exec_command(int **fd, t_token *token, t_msh *ms, int *pid);

/*
** built-in functions
*/
void	echo_execution(char **args);
void	cd_execution(char **args, t_env *head);
void	pwd_execution(void);
void	env_execution(t_env *env, char **args);
void	export_execution(t_env *ms, char **args);
void	unset_execution(t_env *ms, char **args);
void	exit_execution(void);

/*
** utils for exec functions
*/
int		ft_arrlen(char **s);
int		ft_isenv(char *s);
char	**get_env_arr(t_env *export);
void	cmd_not_found(char *cmd);
char	*triplejoin(char *s1, char *s2, char *s3);
void	ft_error(char *cmd, char *arg, char *err, int flag);
void	env_error(char *cmd);
void	bubblesort(char **values);
void	print_export(t_env *export);

/*
** utils for list
*/
int		ft_lstsize(t_env *lst);
char	**lsttoarr(t_env *lst);
void	ft_lstadd_back(t_env *lst, t_env *new);
void	ft_poplst(t_env *lst, t_env *root);
t_env	*ft_lstnew(char *key, char *value);
t_env	*ft_getenv(t_env *head, char *env);

/*
** signals
*/
void	sig_handler(int handler);
void	quit_handler(int handler);

#endif

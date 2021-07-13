#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <dirent.h>
# include <sys/errno.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../lib/libft/libft.h"

# define COMMAND 1
# define PIPE 2
# define REDIRECT_ST_OUTPUT 3
# define APPEND 4
# define REDIRECT_ST_INPUT 5
# define HEREDOC 6

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_token
{
	int				type;
	char			**args;
	struct s_token	*next;
}					t_token;

typedef struct s_msh
{
	t_token		*tokens;
	t_env		*env_list;
	char		*prompt;
	char		*line;
	char		**env;
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
char	*treat_slash(char *str, int *i);
char	*treat_double_quotes(char *str, int *i, t_env *env);
char	*treat_dollar(char *str, int *i, t_env *env);
char	**get_args(char *line, int i);
void	put_to_tokens_list(t_msh *ms, t_token *new);
void	treat_redirections(t_msh *ms, int *i, int j);
void	treat_separator(t_msh *ms, int i, int j, int type);
int		check_single_quotes(char *line, int *i);
int		check_double_quotes(char *line, int *i);

/*
** Exec functions
*/
int		check_execve_functions(t_msh *ms, t_env *head);
void	check_functions(t_msh *ms);

/*
** built-in functions
*/
void	echo_execution(char **args, int i);
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
int		ft_isenv(int c);
char	**get_env_arr(t_env *export);
void	cmd_not_found(char *cmd);
char	*triplejoin(char *s1, char *s2, char *s3);
void	ft_error(char *cmd, char *arg, int err);
void	env_error(char *cmd);
void	bubblesort(char **values);
void	print_export(t_env *export);

/*
** utils for list
*/
int		ft_lstsize(t_env *lst);
void	ft_lstadd_back(t_env *lst, t_env *new);
void	ft_poplst(t_env *lst, t_env *root);
t_env	*ft_lstnew(char *key, char *value);
t_env	*ft_getenv(t_env *head, char *env);

#endif

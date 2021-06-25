#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
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

typedef struct	s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct		s_token
{
	int				type;
	char			**args;
	struct s_token	*next;
}					t_token;

typedef struct	s_msh
{
	t_token		*tokens;
	t_env		*env_list;
	char		*prompt;
	char		*line;
}				t_msh;

void	get_env_list(char **env, t_msh *ms);
void	parse_execute(t_msh *ms);
void	parse_line(t_msh *ms);
void	check_for_syntax_errors(t_msh *ms);
void	error_function(t_msh *ms, char *error);
char	*treat_single_quotes(char *str, int *i);
char	*treat_slash(char *str, int *i);
char	*treat_double_quotes(char *str, int *i, t_env *env);
char	*treat_dollar(char *str, int *i, t_env *env);
char	**get_args(char *line, int i);
void	put_to_tokens_list(t_msh *ms, t_token *new);
void	treat_redirections(t_msh *ms, int *i, int j);
void	treat_separator(t_msh *ms, int i, int j, int type);

#endif

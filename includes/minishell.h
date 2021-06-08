#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <term.h>
# include <curses.h>
# include "../lib/libft/libft.h"


typedef struct	s_env
{
	char			*key;
	char			*key_value;
	struct s_env	*next;
}				t_env;

typedef struct		s_token
{
	char			*type;
	char			**args;
	struct s_token	*next;
}					t_token;

typedef struct		s_history
{
	char				*line;
	struct s_history	*next;
	struct s_history	*prev;
}					t_history;


typedef struct	s_msh
{
	t_token			*tokens;
	t_env			*env_list;
	t_history		*hist;
	struct termios	ch_atr;
	struct termios	saved_attributes;
	char			*term_name;
	char			*line;
	char			*buf;
}				t_msh;

void	get_env_list(char **env, t_msh *ms);
void	parse_execute(t_msh *ms);
void	treat_up(t_msh *ms);
void	treat_down(t_msh *ms);
void	treat_backspace(t_msh *ms);
void	treat_enter(t_msh *ms);
void	save_to_history(t_msh *ms);
void	parse_line(t_msh *ms);

#endif

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
	char			*var;
	char			*var_value;
	struct s_env	*next;
}				t_env;

typedef struct		s_token
{
	char			*type;
	char			**command;
	struct s_token	*next;
}					t_token;

typedef struct	s_msh
{
	t_token			*tokens;
	t_env			*env_list;
	struct termios	ch_atr;
	struct termios	saved_attributes;
	char			*term_name;
	char			*line;
	char			*buf;
}				t_msh;

#endif

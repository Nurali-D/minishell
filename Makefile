NAME = minishell

HEAD = includes/

PARSDIR = srcs/parser/
EXECDIR = srcs/execution/
BUILTIN = srcs/execution/builtin_functions/
UTILS = srcs/execution/utils/

LIB = lib/

PARSFILES = main.c parse_execute.c env_list.c parser.c syntax_error.c \
		parser_utils.c parser_utils2.c put_to_tokens.c free_functions.c \
		syntax_error2.c dollar_question.c check_infiles.c find_redirections.c \
		find_redirections_utils.c read_from_heredoc.c save_fdout.c \
		replace_extended_ascii.c \

EXECFILES = start.c execute_commands.c make_forks.c exec_command.c execve.c signal.c \
			
BUILTINFILES = echo.c cd.c pwd.c export.c unset.c env.c exit.c

UTILSFILES = utils.c error.c lst_utils.c exit_utils.c export_utils.c sort.c

SRCS =	$(addprefix $(PARSDIR), $(PARSFILES)) $(addprefix $(EXECDIR), $(EXECFILES)) \
		$(addprefix $(BUILTIN), $(BUILTINFILES)) $(addprefix $(UTILS), $(UTILSFILES))

OBJS = ${SRCS:.c=.o}

CC = gcc -g -Wall -Wextra -Werror

RM = rm -f

CFLAGS = -I $(HEAD)

FLAGS = -L $(LIB)libft -lft \
		-L/usr/local/Cellar/readline/8.1/lib/ \
		-I/usr/local/Cellar/readline/8.1/include/readline/ \
		-lreadline \

$(NAME) : $(OBJS) $(HEAD)*.h
	@make -C $(LIB)libft all
	${CC} ${CFLAGS} $(OBJS) lib/libft/ft_strcmp.c $(FLAGS)  -o ${NAME}

%.o: %.c $(HEAD)
	$(CC) -c  $< -o $@ -I$(HEAD)

all: ${NAME}

clean:
	make clean -C $(LIB)libft
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}
	make fclean -C $(LIB)libft


re: fclean all

bonus: all

norme:
	norminette -R CheckForbiddenSourceHeader $(SRCS) $(HEAD)*.h

.PHONY: all clean fclean re norme bonuss

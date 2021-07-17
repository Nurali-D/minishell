NAME = minishell

HEAD = includes/

PARSDIR = srcs/parser/
EXECDIR = srcs/execution/

LIB = lib/

PARSFILES = main.c parse_execute.c env_list.c parser.c syntax_error.c error_function.c \
		parser_utils.c parser_utils2.c parse_redirections.c parse_pipe.c \
		syntax_error2.c dollar_question.c \

EXECFILES = builtin_functions.c builtin_functions2.c error.c utils.c execution.c sort.c lst_utils.c \

SRCS = $(addprefix $(PARSDIR), $(PARSFILES)) $(addprefix $(EXECDIR), $(EXECFILES))

OBJS = ${SRCS:.c=.o}

CC = gcc -g -Wall -Wextra -Werror

RM = rm -f

CFLAGS = -I $(HEAD)

FLAGS = -L $(LIB)libft -lft \
		-L/Users/$(USER)/.brew/Cellar/readline/8.1/lib/ \
		-I/Users/$(USER)/.brew/Cellar/readline/8.1/include/readline/ \
		-lreadline \

$(NAME) : $(OBJS) $(HEAD)*.h
	@make -C $(LIB)libft all
	${CC} ${CFLAGS} $(OBJS) $(FLAGS)  -o ${NAME}

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
	norminette -R CheckForbiddenSourceHeader $(PARSDIR)*.c $(EXECDIR)*.c $(HEAD)*.h

.PHONY: all clean fclean re norme bonuss

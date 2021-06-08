
NAME = minishell

HEAD = includes/

SRCDIR = srcs/

LIB = lib/

FILES = main.c parse_execute.c env_list.c shell_history.c keys_functions.c parser.c \

SRCS = $(addprefix $(SRCDIR), $(FILES))

OBJS = ${SRCS:.c=.o}

CC = gcc -g

RM = rm -f

CFLAGS = -I $(HEAD) -Wall -Wextra -Werror

FLAGS = -L $(LIB)libft -lft -ltermcap

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
	norminette -R CheckForbiddenSourceHeader $(SRCDIR)*.c $(HEAD)*.h

.PHONY: all clean fclean re norme bonus

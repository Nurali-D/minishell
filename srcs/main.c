#include "minishell.h"

t_env	*get_new_list_element(t_env *new, t_env *head)
{
	t_env	*temp;

	temp = head;
	while (temp)
	{
		if (!(temp->next))
			break;
		temp = temp->next;
	}
	if (!(head))
		head = new;
	else
		temp->next = new;
	return (head);
}

void	get_env_list(char **env, t_msh *ms)
{
	char	**splitted;
	int		i;
	t_env	*temp;

	i = 0;
	while (env[i])
	{
		temp = (t_env *)malloc(sizeof(t_env));
		// if (!temp)
		// 	error_free(ms);
		temp->next = NULL;
		splitted = ft_split(env[i], '=');
		temp->var = splitted[0];
		temp->var_value = splitted[1];
		ms->env_list = get_new_list_element(temp, ms->env_list);
		i++;
	}
}

void	init_ms(t_msh *ms)
{
	ms->env_list = NULL;
	ms->tokens = NULL;
}

int	main(int argc, char **argv, char **env)
{
	t_msh			ms;
	struct termios	ch_atrr;
	char			*term_name;
	char			buf[200];
	int				n;

	init_ms(&ms);
	get_env_list(env, &ms);
	term_name = "xterm-256color";
	tcgetattr(0, &ch_atrr);
	ch_atrr.c_lflag &= ~(ECHO);
	ch_atrr.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &ch_atrr);
	tgetent(0, term_name);
	tputs(save_cursor, 1, ft_putchar);
	while (1)
	{
		// write(1, "my-shell$", 9);
		n = read(0, buf, 100);
		if (!strcmp(buf, "\e[A"))
		{
			tputs(restore_cursor, 1, ft_putchar);
			tputs(tgetstr("ed", 0), 1, ft_putchar);
			printf("previos\n");
		}
		else if (!strcmp(buf, "\e[B"))
			printf("next\n");
		else if (!strcmp(buf, key_backspace))
			tputs(delete_character, 1, ft_putchar);
		else
			write(1, buf, n);
	}
	// write(1, "\n", 1);
	return (0);
}

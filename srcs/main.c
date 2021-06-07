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
		temp->next = NULL;
		splitted = ft_split(env[i], '=');
		temp->key = splitted[0];
		temp->key_value = splitted[1];
		ms->env_list = get_new_list_element(temp, ms->env_list);
		i++;
	}
}

void	init_ms(t_msh *ms)
{
	ms->env_list = NULL;
	ms->tokens = NULL;
	ms->line = (char *)malloc(sizeof(char));
	ms->buf = (char *)malloc(sizeof(char) * 10);
	ms->term_name = "xterm-256color";
}

void	change_term_attributes(t_msh *ms)
{
	tcgetattr(0, &ms->saved_attributes);
	ms->ch_atr = ms->saved_attributes;
	ms->ch_atr.c_lflag &= ~(ECHO);
	ms->ch_atr.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &ms->ch_atr);
	tgetent(0, ms->term_name);
	write(1, "my-shell$ ", 10);
	tputs(save_cursor, 1, ft_putchar);
}

void	save_printable(t_msh *ms)
{
	char	*tmp;

	tmp = ms->line;
	if (ft_isprint(ms->buf[0]))
	{
		ms->line = ft_strjoin(ms->line, ms->buf);
		free(tmp);
	}
}

void	parse_line(t_msh *ms)
{
	write(1, "\n", 1);
	write(1, ms->line, ft_strlen(ms->line));
	ft_bzero(ms->line, ft_strlen(ms->line));
}

void	treat_keys(t_msh *ms)
{
	int	n;

	while (1)
	{
		n = read(0, ms->buf, 10);
		save_printable(ms);
		if (!ft_strcmp(ms->buf, "\e[A")) // up arrow
		{
			tputs(restore_cursor, 1, ft_putchar);
			tputs(tgetstr("ce", 0), 1, ft_putchar);
			write(1,"previos", 7);
		}
		else if (!ft_strcmp(ms->buf, "\e[B")) // down arrow
		{
			tputs(restore_cursor, 1, ft_putchar);
			tputs(tgetstr("ce", 0), 1, ft_putchar);
			write(1, "next", 4);
		}
		else if (!ft_strcmp(ms->buf, "\x7f"))  // backspace
		{
			tputs(tgetstr("le", 0), 1, ft_putchar);
			tputs(delete_character, 1, ft_putchar);
		}
		else if (!ft_strcmp(ms->buf, "\n")) // enter
		{
			parse_line(ms);
			write(1, "\n", 1);
			write(1, "my-shell$ ", 10);
			tputs(save_cursor, 1, ft_putchar);
		}
		else // other keys
			write(1, ms->buf, n);
		ft_bzero(ms->buf, 10);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_msh	ms;

	init_ms(&ms);
	get_env_list(env, &ms);
	change_term_attributes(&ms);
	treat_keys(&ms);
	return (0);
}

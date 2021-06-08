#include "minishell.h"

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

void	treat_keys(t_msh *ms)
{
	int	n;

	while (1)
	{
		n = read(0, ms->buf, 10);
		save_printable(ms);
		if (!ft_strcmp(ms->buf, "\e[A")) // up arrow
			treat_up(ms);
		else if (!ft_strcmp(ms->buf, "\e[B")) // down arrow
			treat_down(ms);
		else if (!ft_strcmp(ms->buf, "\x7f"))  // backspace
			treat_backspace(ms);
		else if (!ft_strcmp(ms->buf, "\n")) // enter
			treat_enter(ms);
		else if (!ft_strcmp(ms->buf, "\e[C") || !ft_strcmp(ms->buf, "\e[D")) //right-> and left<-
			;
		else // other keys
			write(1, ms->buf, n);
		ft_bzero(ms->buf, 10);
	}
}

void	parse_execute(t_msh *ms)
{
	change_term_attributes(ms);
	treat_keys(ms);
}

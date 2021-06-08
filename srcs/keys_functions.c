#include "minishell.h"

void	treat_up(t_msh *ms)
{
	tputs(restore_cursor, 1, ft_putchar);
	tputs(tgetstr("ce", 0), 1, ft_putchar);
	get_line_from_history(ms, 1);
}

void	treat_down(t_msh *ms)
{
	tputs(restore_cursor, 1, ft_putchar);
	tputs(tgetstr("ce", 0), 1, ft_putchar);
	get_line_from_history(ms, 2);
}

void	treat_backspace(t_msh *ms)
{
	if (ft_strlen(ms->line))
	{
		tputs(tgetstr("le", 0), 1, ft_putchar);
		tputs(delete_character, 1, ft_putchar);
		ms->line[ft_strlen(ms->line) - 1] = '\0';
	}
}

void	treat_enter(t_msh *ms)
{
	save_to_history(ms);
	parse_line(ms);
	write(1, "\n", 1);
	write(1, "my-shell$ ", 10);
	tputs(save_cursor, 1, ft_putchar);
	ms->tmp = NULL;
}


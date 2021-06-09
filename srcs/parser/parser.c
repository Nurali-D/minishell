#include "minishell.h"

void	parse_line(t_msh *ms)
{
	write(1, "\n", 1);
	write(1, ms->line, ft_strlen(ms->line));
	ft_bzero(ms->line, ft_strlen(ms->line));
}

#include "minishell.h"

static t_history	*get_new_hist_element(t_history *new, t_history *head)
{
	t_history	*temp;

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
	{
		temp->next = new;
		new->prev = temp;
	}
	return (head);
}

void	save_to_history(t_msh *ms)
{
	t_history	*temp;

	temp = (t_history *)malloc(sizeof(t_history));
	temp->next = NULL;
	temp->prev = NULL;
	temp->line = ft_strdup(ms->line);
	ms->hist = get_new_hist_element(temp, ms->hist);
}

static void	move_up(t_msh *ms)
{
	t_history	*tmp;

	if (ms->tmp)
			if (ms->tmp->prev)
			{
				tmp = ms->tmp->prev;
				write(1, tmp->line, ft_strlen(tmp->line));
				ms->tmp = tmp;
			}
			else
				return ;
	else if (ms->hist)
	{
		tmp = ms->hist;
		while (tmp)
		{
			if (!(tmp->next))
				break;
			tmp = tmp->next;
		}
		write(1, tmp->line, ft_strlen(tmp->line));
		ms->tmp = tmp;
	}
}

static void	move_down(t_msh *ms)
{
	t_history	*tmp;

	if (ms->tmp)
		if (ms->tmp->next)
		{
			tmp = ms->tmp->next;
			write(1, tmp->line, ft_strlen(tmp->line));
			ms->tmp = tmp;
		}
}

void	get_line_from_history(t_msh *ms, int flag)
{
	if (flag == 1)
		move_up(ms);
	else
		move_down(ms);
}

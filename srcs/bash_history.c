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
	temp->line = ms->line;
	ms->hist = get_new_hist_element(temp, ms->hist);
}

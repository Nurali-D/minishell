#include "minishell.h"

int	ft_lstsize(t_env *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

t_env	*ft_lstlast(t_env *lst)
{
	if (lst)
		while (lst->next)
			lst = lst->next;
	return (lst);
}

t_env	*ft_lstnew(char *key, char *value)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back(t_env *lst, t_env *new)
{
	t_env	*last;

	if (lst)
	{
		last = ft_lstlast(lst);
		last->next = new;
	}
	else
		lst = new;
}

void	ft_poplst(t_env *lst, t_env *root)
{
	t_env	*tmp;

	tmp = root;
	if (lst)
	{
		while (tmp->next != lst)
		{
			tmp = tmp->next;
		}
		tmp->next = lst->next;
		free(lst);
	}
}

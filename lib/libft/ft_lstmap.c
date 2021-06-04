/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltulune <ltulune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 23:47:38 by ltulune           #+#    #+#             */
/*   Updated: 2021/06/04 12:45:37 by ltulune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *ls, void *(*f)(void *), void (*dl)(void *))
{
	t_list	*new_lst;
	t_list	*new_el;

	if (!f || !dl)
		return (NULL);
	new_lst = NULL;
	while (ls)
	{
		new_el = ft_lstnew(f(ls->content));
		if (!(new_el))
		{
			ft_lstclear(&new_lst, dl);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, new_el);
		ls = ls->next;
	}
	return (new_lst);
}

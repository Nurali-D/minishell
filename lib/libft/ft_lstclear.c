/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltulune <ltulune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 17:49:35 by ltulune           #+#    #+#             */
/*   Updated: 2020/11/16 18:03:15 by ltulune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*el;
	t_list	*buf;

	el = *lst;
	while (el)
	{
		buf = el->next;
		if (del)
			del(el->content);
		free(el);
		el = buf;
	}
	*lst = NULL;
}

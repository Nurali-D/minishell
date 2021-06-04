/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltulune <ltulune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 21:37:54 by ltulune           #+#    #+#             */
/*   Updated: 2020/12/09 14:14:33 by ltulune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int					check_rem_for_bsn(char **r, char **l)
{
	char			*bsn;
	char			*tmp;

	if (*r && (bsn = ft_strchr(*r, '\n')))
	{
		*bsn = '\0';
		if (!(*l = ft_strjoin_mod(*l, *r)))
			return (-1);
		bsn++;
		if (!(tmp = ft_strdup(bsn)))
			return (-1);
		free(*r);
		*r = tmp;
		return (1);
	}
	return (0);
}

int					save_and_return(int fd, char **line, char **rem, char *buf)
{
	int				n_buf;
	char			*tmp;

	while ((n_buf = read(fd, buf, BUFFER_SIZE)))
	{
		if ((buf[n_buf] = '\0') == '\0'
		&& !(tmp = ft_strjoin_mod(*rem, buf)))
			return (-1);
		free(*rem);
		if ((*rem = tmp) && (check_rem_for_bsn(rem, line)) == 1)
			return (1);
		else if (check_rem_for_bsn(rem, line) == -1)
			return (-1);
	}
	if (!*line && !*rem)
	{
		if (!(*line = (char*)malloc(sizeof(char))))
			return (-1);
		*line[0] = '\0';
	}
	else if (!(*line = ft_strjoin_mod(*line, *rem)) || n_buf < 0)
		return (-1);
	free(*rem);
	*rem = NULL;
	return (0);
}

int					get_line(int fd, char **line, char **rem)
{
	char			buf[BUFFER_SIZE + 1];

	if ((fd < 0 || line == NULL || read(fd, buf, 0) < 0) || BUFFER_SIZE < 1
	|| BUFFER_SIZE > 8200000)
		return (-1);
	*line = NULL;
	if (check_rem_for_bsn(rem, line) == 1)
		return (1);
	else if (check_rem_for_bsn(rem, line) == -1)
		return (-1);
	return (save_and_return(fd, line, rem, buf));
}

t_list				*nl_fl(int fd, t_list *head, t_list *tmp, int f)
{
	t_list			*new;
	t_list			*temp;

	if (f == 1)
	{
		if (!(new = (t_list*)malloc(sizeof(t_list))))
			return (NULL);
		new->fd = fd;
		new->rem = NULL;
		new->next = NULL;
		return (new);
	}
	if ((temp = head) && temp != tmp)
	{
		while (temp->next != tmp)
			temp = temp->next;
		temp->next = tmp->next;
		free(tmp);
		return (head);
	}
	temp = tmp->next;
	free(head);
	head = temp;
	return (head);
}

int					get_next_line(int fd, char **line)
{
	static t_list	*head;
	t_list			*tmp;
	int				i;

	tmp = NULL;
	if (!head && !(head = nl_fl(fd, head, tmp, 1)))
		return (-1);
	tmp = head;
	while (tmp->fd != fd)
	{
		if (tmp->next == NULL)
		{
			if (!(tmp->next = nl_fl(fd, head, tmp, 1)))
				return (-1);
		}
		tmp = tmp->next;
	}
	if ((i = get_line(tmp->fd, line, &tmp->rem)) != 1)
		head = nl_fl(fd, head, tmp, 2);
	return (i);
}

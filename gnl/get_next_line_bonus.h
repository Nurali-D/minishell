/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltulune <ltulune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 21:43:10 by ltulune           #+#    #+#             */
/*   Updated: 2020/12/03 00:57:51 by ltulune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <unistd.h>
# include <stdlib.h>
# include <string.h>

typedef struct	s_list
{
	int				fd;
	char			*rem;
	struct s_list	*next;
}				t_list;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 20
# endif

int				get_next_line(int fd, char **line);
size_t			ft_strlen(const char *s);
char			*ft_strjoin_mod(char const *s1, char const *s2);
char			*ft_strdup(const char *s1);
char			*ft_strchr(const char *s, int c);

#endif

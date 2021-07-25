#include "libft.h"

int	ft_putchar(int c)
{
	ssize_t	i;

	i = write(1, &c, 1);
	if (i < 0)
		return (EOF);
	return (c);
}

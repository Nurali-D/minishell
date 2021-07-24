#include "minishell.h"

void	bubblesort(char **values)
{
	int		i;
	int		j;
	int		arrlen;
	char	*tmp;

	i = 0;
	arrlen = ft_arrlen(values);
	while (i + 1 < arrlen)
	{
		j = 0;
		while (j + 1 < arrlen - i)
		{
			if (values[j + 1] && (ft_strcmp(values[j], values[j + 1])) > 0)
			{
				tmp = values[j];
				values[j] = values[j + 1];
				values[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

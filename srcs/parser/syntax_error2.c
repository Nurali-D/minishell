#include "minishell.h"

int	check_single_quotes(char *line, int *i)
{
	int	j;

	j = *i;
	while (line && line[++j])
	{
		if (line[j] == '\'')
		{
			*i = j;
			return 0;
		}
	}
	printf("Not interpret unclosed quotes!\n");
	return 1;
}

int	check_double_quotes(char *line, int *i)
{
	int	j;

	j = *i;
	while (line && line[++j])
	{
		if (line[j] == '"' && i > 0 && line[j - 1] != '\\')
		{
			*i = j;
			return 0;
		}
	}
	printf("Not interpret unclosed quotes!\n");
	return 1;
}

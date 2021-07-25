#include "minishell.h"

void	error_function(t_msh *ms, char *error)
{
	// free_structure(ms);
	(void)ms;
	printf("%s\n", error);
	// exit(2);
}

void	free_array(char **array)
{
	int		i;


	i = 0;
	while (array && array[i])
	{
		free(array[i]);
		i++;
	}
	free(array[i]);
	free(array);
}
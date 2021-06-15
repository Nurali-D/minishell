#include "minishell.h"

void	error_function(t_msh *ms, char *error)
{
	// free_structure(ms);
	(void)ms;
	printf("%s\n", error);
	// exit(2);
}
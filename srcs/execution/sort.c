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
			if ((ft_strcmp(values[j], values[j + 1])) > 0)
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

// void	sort(t_env *env)
// {
// 	t_env	*p;
// 	t_env	*key;
// 	t_env	*result;

// 	result = env;
// 	env = env->next;
// 	result->next = NULL;
// 	while (env->next != NULL)
// 	{
// 		key = env;
// 		env = env->next;
// 		if (key->key < result->key)
// 		{
// 			key->next = result;
// 			result = key;
// 		}
// 		else
// 		{
// 			p = result;
// 			while (p->next != NULL)
// 			{
// 				if (p->next->key > key->key)
// 					break;
// 				p = p->next;
// 			}
// 			key->next = p->next;
// 			p->next = key;
// 		}
// 	}
// 	env = result;
// }

/*
void	combsort(char **values)
{
	const double	factor = 1.247; // Фактор уменьшения
	double			step = ft_arrlen(values);
	int				arrlen = ft_arrlen(values);
	int i;

	while (step >= 1)
	{
		i = 0;
		while (i + step < arrlen)
		{
    		if ((ft_strcmp(values[i], values[i + step])) > 0)
			{
    	    	swap(values[i], values[i + step]);
			}
			i++;
    	}
    	step /= factor;
	}
}
*/

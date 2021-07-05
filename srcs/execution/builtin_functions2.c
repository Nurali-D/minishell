#include "minishell.h"

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

void	print_export(t_env *export)
{
	ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(export->key, 1);
	ft_putstr_fd("=\"", 1);
	ft_putstr_fd(export->value, 1);
	ft_putstr_fd("\"\n", 1);
}

// не отрабатывает добавление корректно, записывает муссор
// решил изменить сотрировку, чтобы в дальнейшем было проще работать

void	export_execution(t_msh *ms)
{
	t_env *tmp;
	int		i;
	int		j;
	char	**res;

	// sort(tmp);
	// env = get_env_arr(ms);
	// bubblesort(env);
	tmp = ms->env_list;
	if (!ms->tokens->args[1])
	{
		while (tmp)
		{
			print_export(tmp);
			tmp = tmp->next;
		}
	}
	else
	{
		i = 0;
		while (ms->tokens->args[++i])
		{
			res = ft_split(ms->tokens->args[i], '='); // обработать error
			ft_lstadd_back(ms->env_list, ft_lstnew(res[0], res[1]));
			j = -1;
			while (res[++j])
				free(res[j]);
			free(res);
		}
	}
	printf("\e[1;92mbuilt-in function\n\e[0m");
}

void	unset_execution(void)
{
	printf("\e[1;92mbuilt-in function\n\e[0m");
	return ;
}

void	exit_execution(void)
{
	printf("\e[1;92mbuilt-in function\n\e[0m");
	return ;
}

#include "minishell.h"

static int	ft_isspace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

long long int	ft_atol(const char *str)
{
	int				i;
	long long int	res;
	long long int	sign;

	i = 0;
	res = 0;
	sign = 1;
	while (ft_isspace(str[i]))
		i++;
	if ((str[i] == 45) || (str[i] == 43))
	{
		if (str[i] == 45)
			sign = sign * -1;
		i++;
	}
	while ((str[i] >= 48) && (str[i] <= 57))
	{
		res = 10 * res + (str[i] - 48);
		i++;
	}
	return (res * sign);
}

void	exit_execution(char **args)
{
	long long int	check;
	char			*res;

	check = 0;
	g_status = 0;
	ft_putendl_fd("exit", 1);
	if (args[1])
	{
		check = ft_atol(args[1]);
		res = ft_ltoa(check);
		if ((ft_strcmp(args[1], res)) != 0)
		{
			ft_error(args[0], args[1], "numeric argument required", 255);
			exit(g_status);
		}
		else if (args[2])
		{
			ft_error(args[0], NULL, "too many arguments", 1);
			return ;
		}
	}
	exit(g_status);
}

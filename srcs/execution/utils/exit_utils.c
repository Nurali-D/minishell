#include "minishell.h"

static int	ft_intlen(long long int num)
{
	int			i;

	i = 0;
	while (num)
	{
		num /= 10;
		i++;
	}
	return (i);
}

static void	ft_wrnum2(char *b, long long int c, int i)
{
	b[i] = '\0';
	while (c)
	{
		b[i - 1] = c % 10 + '0';
		c /= 10;
		i--;
	}
}

static char	*ft_wrnum(char *b, long long int c)
{
	int						i;
	int						j;
	unsigned long long int	nb;

	i = ft_intlen(c);
	j = i;
	if (c < 0 && i > 0)
	{
		b[0] = '-';
		nb = c * -1;
		b[i + 1] = '\0';
		while (nb)
		{
			b[i] = (char)(nb % 10 + 48);
			nb /= 10;
			i--;
		}
	}
	else if (j > 0)
		ft_wrnum2(b, c, j);
	return (b);
}

char	*ft_ltoa(long long int n)
{
	char			*ret;
	long long int	nl;

	ret = (char *)malloc((ft_intlen(n) + 2) * sizeof(char));
	if (!(ret))
		return (NULL);
	nl = n;
	if (n == 0)
	{
		ret[0] = '0';
		ret[1] = '\0';
		return (ret);
	}
	return (ft_wrnum(ret, nl));
}

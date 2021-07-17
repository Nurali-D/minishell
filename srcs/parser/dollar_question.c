#include "minishell.h"

char	*replace_question_mark(char *str, int *i)
{
	char	*before_question;
	char	*status;
	char	*after_question;
	char	*ret;
	char	*tmp;

	before_question = ft_substr(str, 0, *i);
	status = ft_itoa(g_status);
	after_question = ft_strdup(str + *i + 2);
	*i += ft_strlen(status);
	ret = ft_strjoin(before_question, status);
	tmp = ret;
	ret = ft_strjoin(ret, after_question);
	free(tmp);
	free(before_question);
	free(status);
	free(after_question);
	return (ret);

}

#include "minishell.h"

void	ft_strjoin_redir(char **result, char *tmp, char *start);
void	ft_strjoin_redir_env(char **result, char **get_tmp, char *start);

char	*ft_string_check_env(char *line)
{
	char	*tmp;
	char	*start;
	char	*result;

	result = ft_calloc(1, 1);
	tmp = line;
	start = tmp;
	while (*tmp)
	{
		if (*tmp == '$' && ft_check_start_set(*(tmp + 1)))
		{
			ft_strjoin_redir_env(&result, &tmp, start);
			start = tmp;
		}
		else
			tmp++;
	}
	ft_strjoin_redir(&result, tmp, start);
	free(line);
	return (result);
}

void	ft_strjoin_redir_env(char **result, char **get_tmp, char *start)
{
	char	*tmp;
	char	*value;
	char	*content;

	tmp = *get_tmp;
	ft_strjoin_redir(result, tmp, start);
	tmp++;
	start = tmp;
	while (ft_isalnum(*tmp) || *tmp == '_')
		tmp++;
	value = ft_substr(start, 0, tmp - start);
	if (!value)
		ft_exit("minishell: read_redirect: getset: ", "error");
	content = ft_getset(value);
	free(value);
	ft_strjoin_string(result, content);
	*get_tmp = tmp;
}

void	ft_strjoin_redir(char **result, char *tmp, char *start)
{
	char	*value;

	value = ft_substr(start, 0, tmp - start);
	if (!value)
		ft_exit("minishell: read_redirect: getset: ", "error");
	ft_strjoin_string(result, value);
}

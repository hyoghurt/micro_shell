#include "minishell.h"

void	ft_strjoin_string(char **string, char *content)
{
	char	*tmp;

	if (*string)
	{
		tmp = ft_strjoin(*string, content);
		free(*string);
		free(content);
		content = tmp;
	}
	*string = content;
}

void	ft_content(char **string, char *start)
{
	char	*content;

	content = ft_substr(start, 0, shell.line - start);
	if (!content)
		ft_free_string(string);
	ft_strjoin_string(string, content);
}

void	ft_free_string(char **string)
{
	if (*string)
		free(string);
	*string = 0;
}

int		ft_check_set(char check)
{
	if ((check == '_' || ft_isalpha(check)))
		return (1);
	return (0);
}

char	*ft_value_getset(void)
{
	char	*start;
	char	*tmp;
	char	*content;

	start = shell.line;
	while (ft_isalnum(*shell.line) || *shell.line == '_')
		shell.line++;
	tmp = ft_substr(start, 0, shell.line - start);
	if (!tmp)
		return (0);
	content = ft_getset(tmp);
	free(tmp);
	return (content);
}

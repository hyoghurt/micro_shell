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

	content = ft_substr(start, 0, g_shell.line - start);
	if (!content)
		ft_exit("minishell: content: malloc: ", "error");
	ft_strjoin_string(string, content);
}

void	ft_free_string(char **string)
{
	if (*string)
		free(string);
	*string = 0;
}

int	ft_check_start_set(char check)
{
	if ((check == '_' || ft_isalpha(check)))
		return (1);
	return (0);
}

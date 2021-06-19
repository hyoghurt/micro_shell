#include "minishell.h"

void	ft_string_ecran(char **string)
{
	char	*start;

	start = ++g_shell.line;
	g_shell.line++;
	ft_content(string, start);
}

void	ft_string_status(char **string)
{
	char	*content;

	g_shell.line += 2;
	content = ft_itoa(g_shell.status);
	if (!content)
		ft_free_string(string);
	ft_strjoin_string(string, content);
}

void	ft_string_env(char **string)
{
	char	*content;

	g_shell.line++;
	content = ft_value_getset();
	if (content)
		ft_strjoin_string(string, content);
}

void	ft_string_word(char **string)
{
	char	*start;

	start = g_shell.line++;
	while (!ft_strchr(" \t><\'\"\\$;|", *g_shell.line))
		g_shell.line++;
	ft_content(string, start);
}

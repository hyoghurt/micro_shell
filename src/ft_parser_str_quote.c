#include "minishell.h"

static int	ft_check_ecran(char c1, char c2)
{
	if (c1 == '\\')
	{
		if (ft_strchr("\\$\"", c2))
			return (1);
	}
	return (0);
}

void	ft_string_quote_one(char **string)
{
	char	*start;

	start = ++g_shell.line;
	while (*g_shell.line != '\'')
		g_shell.line++;
	ft_content(string, start);
	g_shell.line++;
}

void	ft_string_quote_two(char **string, int f)
{
	char	*start;

	start = ++g_shell.line;
	while (*g_shell.line != '\"')
	{
		if (ft_check_set(*g_shell.line, *(g_shell.line + 1)) && f != 2)
		{
			ft_content(string, start);
			ft_string_env(string);
			start = g_shell.line;
		}
		else if (ft_check_ecran(*g_shell.line, *(g_shell.line + 1)))
		{
			ft_content(string, start);
			ft_string_ecran(string);
			start = g_shell.line;
		}
		else
			g_shell.line++;
	}
	ft_content(string, start);
	g_shell.line++;
}

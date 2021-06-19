#include "minishell.h"

static int	ft_check_ecran(char check);
static void	ft_string_quote_one(char **string);
static void	ft_string_quote_two(char **string, int f);

void	ft_string_quote(char **string, int f)
{
	if (*g_shell.line == '\'')
		ft_string_quote_one(string);
	else
		ft_string_quote_two(string, f);
}

static void	ft_string_quote_one(char **string)
{
	char	*start;

	start = ++g_shell.line;
	while (*g_shell.line != '\'')
		g_shell.line++;
	ft_content(string, start);
	g_shell.line++;
}

static int	ft_check_ecran(char check)
{
	if (ft_strchr("\\$\"", check))
		return (1);
	return (0);
}

static void	ft_string_quote_two(char **string, int f)
{
	char	*start;

	start = ++g_shell.line;
	while (*g_shell.line != '\"')
	{
		if (*g_shell.line == '$' && ft_check_set(*(g_shell.line + 1)) && f != 2)
		{
			ft_content(string, start);
			ft_string_env(string);
			start = g_shell.line;
		}
		else if (*g_shell.line == '\\' && ft_check_ecran(*(g_shell.line + 1)))
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

#include "minishell.h"

static int	ft_check_ecran(char check);
static void	ft_string_quote_one(char **string, char c);
static void	ft_string_quote_two(char **string, char c);

void	ft_string_quote(char **string, char c)
{
	if (*shell.line == '\'')
		ft_string_quote_one(string, *shell.line);
	else
		ft_string_quote_two(string, *shell.line);
}

static void	ft_string_quote_one(char **string, char c)
{
	char	*start;

	start = ++shell.line;
	while (*shell.line != c)
		shell.line++;
	ft_content(string, start);
	shell.line++;
}

static int	ft_check_ecran(char check)
{
	if (ft_strchr("\\$\"", check))
		return (1);
	return (0);
}

static void	ft_string_quote_two(char **string, char c)
{
	char	*start;

	start = ++shell.line;
	while (*shell.line != c)
	{
		if (*shell.line == '$' && ft_check_set(*(shell.line + 1)))
		{
			ft_content(string, start);
			ft_string_env(string);
			start = shell.line;
		}
		else if (*shell.line == '\\' && ft_check_ecran(*(shell.line + 1)))
		{
			ft_content(string, start);
			ft_string_ecran(string);
			start = shell.line;
		}
		else
			shell.line++;
	}
	ft_content(string, start);
	shell.line++;
}

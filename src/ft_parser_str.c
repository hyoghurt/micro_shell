#include "minishell.h"

char	*ft_crt_string(int f)
{
	char	*string;

	string = 0;
	ft_jump_space();
	while (*g_shell.line && !ft_strchr(" \t<>;|", *g_shell.line))
	{
		if (*g_shell.line == '\\')
			ft_string_ecran(&string);
		else if (*g_shell.line == '\'')
			ft_string_quote_one(&string);
		else if (*g_shell.line == '\"')
			ft_string_quote_two(&string, f);
		else if (ft_check_set(*g_shell.line, *(g_shell.line + 1)) && f != 2)
			ft_string_env(&string);
		else if (ft_check_status(*g_shell.line, *(g_shell.line + 1)) && f != 2)
			ft_string_status(&string);
		else
			ft_string_word(&string);
	}
	return (string);
}

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
	g_shell.status = 0;
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

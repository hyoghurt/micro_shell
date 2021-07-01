#include "minishell.h"

static int	ft_lexer_quote(char **s);
static int	ft_lexer_quote_2(char **s);
static int	ft_lexer_redirect(char **s);
static int	ft_lexer_next(char **s);

int	ft_check_lexer(void)
{
	char	*s;

	s = g_shell.line;
	while (*s)
	{
		if (*s == '\\')
			s++;
		else if (*s == '\'' && ft_lexer_quote(&s))
			return (1);
		else if (*s == '\"' && ft_lexer_quote_2(&s))
			return (1);
		else if (*s == ';' && ft_lexer_next(&s))
			return (1);
		else if (*s == '<' || *s == '>')
		{
			if (ft_lexer_redirect(&s))
				return (1);
		}
		s++;
	}
	return (0);
}

static int	ft_lexer_quote(char **s)
{
	char	*tmp;

	tmp = *s;
	tmp++;
	while (*tmp && *tmp != '\'')
		tmp++;
	if (*tmp == '\0')
		return (1);
	*s = tmp;
	return (0);
}

static int	ft_lexer_quote_2(char **s)
{
	char	*tmp;

	tmp = *s;
	tmp++;
	while (*tmp && *tmp != '\"')
	{
		tmp++;
		if (*tmp && *tmp == '\"' && tmp != g_shell.line && *(tmp - 1) == '\\')
			tmp++;
	}
	if (*tmp == '\0')
		return (1);
	*s = tmp;
	return (0);
}

static int	ft_lexer_redirect(char **s)
{
	char	*tmp;

	tmp = *s;
	if (*tmp == '<' && *(tmp + 1) == '<')
		tmp++;
	else if (*tmp == '>' && *(tmp + 1) == '>')
		tmp++;
	*s = tmp;
	tmp++;
	while (*tmp && (*tmp == ' ' || *tmp == '\t'))
		tmp++;
	if (*tmp == '\0' || *tmp == '<' || *tmp == '>' || *tmp == '|' || *tmp == ';')
		return (1);
	return (0);
}

static int	ft_lexer_next(char **s)
{
	char	*tmp;

	tmp = *s;
	tmp++;
	while (*tmp && (*tmp == ' ' || *tmp == '\t'))
		tmp++;
	if (*tmp && *tmp == ';')
		return (1);
	*s = tmp;
	return (0);
}

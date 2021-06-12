#include "minishell.h"

static void	ft_crt_lst(t_list **list);
static char	*ft_crt_string(void);

void		ft_string_redirect(char **string);
void		ft_string_env(char **string);
void		ft_string_word(char **string);
void		ft_string_quote(char **string, char c);

void		ft_free_string(char **string);
void		ft_strjoin_string(char **string, char *content);
void		ft_content(char **string, char *start);
char		*ft_value_getset(void);

int		ft_check_set(char check, char c)
{
	if ((check == '_' || check == '?' || ft_isalnum(check)) && c == '\"')
		return (1);
	return (0);
}

int		ft_check_ecran(char check, char c)
{
	if (ft_strchr("\\$\"", check) && c == '\"')
		return (1);
	return (0);
}

void	ft_parser(void)
{
	t_cmd	*new;
	t_list	*list;
	char	**token;

	while (*shell.line && *shell.line != ';')
	{
		list = 0;
		ft_crt_lst(&list);
		if (!list)
			ft_exit("minishell: malloc", "error");
		token = ft_crt_arr_bi_from_list(list);
		ft_lstclear(&list, free);
		if (!token)
			ft_exit("minishell: malloc", "error");
		new = ft_cmdnew(token);
		if (!new)
		{
			ft_free_bi(token);
			ft_exit("minishell: malloc", "error");
		}
		ft_cmdadd_back(&shell.cmd_table, new);
		while (*shell.line == '|' || *shell.line == ' ' || *shell.line == '\t')
			shell.line++;
	}
}

static void	ft_crt_lst(t_list **list)
{
	char	*string;
	t_list	*new;

	while (*shell.line && *shell.line != '|' && *shell.line != ';')
	{
		while (*shell.line && ft_strchr(" \t", *shell.line))
			shell.line++;
		if (*shell.line && *shell.line != '|' && *shell.line != ';')
		{
			string = ft_crt_string();
			if (!string)
			{
				ft_lstclear(list, free);
				return ;
			}
			new = ft_lstnew(string);
			if (!new)
			{
				free(string);
				ft_lstclear(list, free);
				return ;
			}
			ft_lstadd_back(list, new);
		}
	}
}

static char	*ft_crt_string(void)
{
	char	*string;

	string = 0;
	while (*shell.line && *shell.line != ';')
	{
		if (ft_strchr("<>", *shell.line))
		{
			ft_string_redirect(&string);
			return (string);
		}
		else if (*shell.line == '\'' || *shell.line == '\"')
			ft_string_quote(&string, *shell.line);
		else if (*shell.line == '$' && ft_check_set(*(shell.line + 1), '\"'))
			ft_string_env(&string);
		else if (*shell.line == '|')
			return (string);
		else if (!ft_strchr(" \t", *shell.line))
			ft_string_word(&string);
		if (ft_strchr(" \t<>", *shell.line))
			return (string);
	}
	return (string);
}

void	ft_string_redirect(char **string)
{
	char	*start;
	char	*content;
	char	*tmp;

	start = shell.line;
	while (ft_strchr("><", *shell.line))
		shell.line++;
	content = ft_substr(start, 0, shell.line - start);
	*string = content;
}

void	ft_free_string(char **string)
{
	if (*string)
		free(string);
	*string = 0;
}

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

char	*ft_value_getset(void)
{
	char	*start;
	char	*tmp;
	char	*content;

	start = shell.line;
	while (!ft_strchr(">< \t\'\"$|;", *shell.line))
		shell.line++;
	tmp = ft_substr(start, 0, shell.line - start);
	if (!tmp)
		return (0);
	content = ft_getset(tmp);
	free(tmp);
	return (content);
}

void	ft_string_env(char **string)
{
	char	*start;
	char	*content;
	char	*tmp;

	shell.line++;
	content = 0;
	if (*shell.line == '?')
	{
		content = ft_strdup(ft_itoa(shell.status));
		if (!content)
			ft_free_string(string);
		shell.line++;
	}
	else if (*shell.line >= '0' && *shell.line <= '9')
		shell.line++;
	else
		content = ft_value_getset();
	if (content)
		ft_strjoin_string(string, content);
}

void	ft_string_word(char **string)
{
	char	*start;

	if (*shell.line == '\\')
	{
		start = ++shell.line;
		shell.line++;
		ft_content(string, start);
	}
	else
	{
		start = shell.line;
		shell.line++;
		while (!ft_strchr(" \t|><\'\"$;", *shell.line))
		{
			if (*shell.line == '\\')
			{
				ft_content(string, start);
				start = ++shell.line;
			}
			shell.line++;
		}
		ft_content(string, start);
	}
}

void	ft_string_quote(char **string, char c)
{
	char	*start;
	char	*content;
	char	*tmp;

	shell.line++;
	start = shell.line;
	while (*shell.line != c)
	{
		if (*shell.line == '$' && ft_check_set(*(shell.line + 1), c))
		{
			ft_content(string, start);
			if (!(*string))
				return ;
			ft_string_env(string);
			start = shell.line;
		}
		else if (*shell.line == '\\' && ft_check_ecran(*(shell.line + 1), c))
		{
			ft_content(string, start);
			if (!(*string))
				return ;
			start = ++shell.line;
			shell.line++;
		}
		else
			shell.line++;
	}
	ft_content(string, start);
	shell.line++;
}

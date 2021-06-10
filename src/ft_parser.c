#include "minishell.h"

void	ft_exit_token(t_list **list)
{
	ft_lstclear(list, free);
	ft_exit("malloc", "error");
}

static void	ft_crt_lst(t_list **list);
static void	ft_new_token(t_list **list, char c);
static char	*ft_word(void);
static char	*ft_quote(char c);
static char	*ft_file(void);
char	*ft_crt_string(void);

void	ft_parser(void)					//create shell.cmd_table  (is it token[0] token[1] ... | token[0] token[1] ...)
{
	t_cmd	*new;
	t_list	*list;
	char	**token;

	while (*shell.line)
	{
		list = 0;
		ft_crt_lst(&list);						//create list separate word before '|' or ';'
		token = ft_crt_arr_bi_from_list(list);	//converted list in char**
		ft_lstclear(&list, free);				//clear list
		if (!token)
			ft_exit("malloc", "error");
		new = ft_cmdnew(token);					//create struct t_cmd
		if (!new)
			ft_exit("malloc", "error");
		ft_cmdadd_back(&shell.cmd_table, new);	//add struct in shell.cmd_table
		if (*shell.line == '|')
			shell.line++;
	}
}

static void	ft_crt_lst(t_list **list)			//create list
{
	char	*string;
	t_list	*new;

	while (*shell.line && *shell.line != '|')
	{
		while (ft_strchr(" \t", *shell.line))
			shell.line++;
		if (*shell.line && *shell.line != '|')
		{
			string = ft_crt_string();
			new = ft_lstnew(string);
			if (!new)
				printf("write error\n");
			ft_lstadd_back(list, new);
		}
	}
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

void	ft_string_env(char **string)
{
	char	*start;
	char	*content;
	char	*tmp;

	shell.line++;
	if (*shell.line == '?')
	{
		content = ft_strdup(ft_itoa(shell.status));
		shell.line++;
	}
	else if (*shell.line >= '0' && *shell.line <= '9')
	{
		content = 0;
		shell.line++;
	}
	else if (ft_strchr(" \t\"", *shell.line))
		content = ft_strdup("$");
	else 
	{
		start = shell.line;
		while (!ft_strchr(">< \t\'\"$|", *shell.line))
			shell.line++;
		tmp = ft_substr(start, 0, shell.line - start);
		content = ft_getset(tmp);
		free(tmp);
	}
	if (content)
	{
		if (*string)
		{
			tmp = ft_strjoin(*string, content);
			free(*string);
			free(content);
			content = tmp;
		}
		*string = content;
	}
}

void	ft_string_word(char **string);
void	ft_string_quote(char **string, char c);
	
char	*ft_crt_string(void)			//create list separate word before '|'
{
	char	*string;

	string = 0;
	while (*shell.line)
	{
		if (ft_strchr("<>", *shell.line))
		{
			ft_string_redirect(&string);
			return (string);
		}
		else if (ft_strchr("\'\"", *shell.line))
			ft_string_quote(&string, *shell.line);
		else if (*shell.line == '$')
			ft_string_env(&string);
		else if (*shell.line == '|')
			return (string);
		else if (!ft_strchr(" \t", *shell.line))
			ft_string_word(&string);				//create char*
		if (ft_strchr(" \t<>", *shell.line))
			return (string);
	}
	return (string);
}

void	ft_string_word(char **string)			// \n or \t word
{
	char	*start;
	char	*content;
	char	*tmp;

	start = shell.line;
	while (!ft_strchr(" \t|><\'\"$", *shell.line))
		shell.line++;
	content = ft_substr(start, 0, shell.line - start);
	if (*string)
	{
		tmp = ft_strjoin(*string, content);
		free(*string);
		free(content);
		content = tmp;
	}
	*string = content;
}

void	ft_string_quote(char **string, char c)		// " or ' word
{
	char	*start;
	char	*content;
	char	*tmp;

	shell.line++;
	start = shell.line;
	while (*shell.line != c)
	{
		if (*shell.line == '$' && c == '\"')
		{
			content = ft_substr(start, 0, shell.line - start);
			if (*string)
			{
				tmp = ft_strjoin(*string, content);
				free(*string);
				free(content);
				content = tmp;
			}
			*string = content;
			ft_string_env(string);
			start = shell.line;
		}
		else
			shell.line++;
	}
	content = ft_substr(start, 0, shell.line - start);
	if (*string)
	{
		tmp = ft_strjoin(*string, content);
		free(*string);
		free(content);
		content = tmp;
	}
	*string = content;
	shell.line++;
}

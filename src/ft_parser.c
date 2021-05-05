#include "minishell.h"

void	ft_exit_token(t_list **list)
{
	printf("exiiiiiiiiiit_tokkkkkkkkkkkkken\n");
	ft_lstclear(list, ft_free_char);
	ft_exit("error");
}

char	*ft_word(void)
{
	char	*start;
	char	*content;

	start = shell.line;
	while (!ft_strchr(" \t\n|;><\'\"$", *shell.line))
		shell.line++;
	content = ft_substr(start, 0, shell.line - start);
	return (content);
}

char	*ft_quote(char c)
{
	char	*start;
	char	*content;

	shell.line++;
	start = shell.line;
	while (*shell.line != c)
		shell.line++;
	content = ft_substr(start, 0, shell.line - start);
	shell.line++;
	return (content);
}

void	ft_new_token(t_list **list, char c)
{
	t_list	*new;
	char	*content;

	if (c)
		content = ft_quote(c);
	else
		content = ft_word();
	if (!content)
		ft_exit_token(list);
	new = ft_lstnew(content);
	if (!new)
		ft_exit_token(list);
	ft_lstadd_back(list, new);
}

char	*ft_strfile(void)
{
	shell.line++;
	while(*shell.line)
	{
		if (ft_strchr("\'\"", *shell.line))
			return (ft_quote(*shell.line));
		else if (!ft_strchr(" \t\n", *shell.line))
			return (ft_word());
		shell.line++;
	}
}

void	ft_in_file(t_list **list)
{
	char	*file;

	file = ft_strfile();
	if (!file)
		ft_exit_token(list);
	shell.in_file = file;
}

int		ft_crtlst(t_list **list)
{
	while (*shell.line)
	{
		if (ft_strchr("\'\"", *shell.line))
			ft_new_token(list, *shell.line);
		//if (*shell.line == '<')
		//	ft_int_file(list);
		if (!ft_strchr(" \t\n", *shell.line))
			ft_new_token(list, 0);
		if (!*shell.line)
			break ;
		if (*shell.line == '|')
		{
			shell.line++;
			return (1);
		}
		shell.line++;
	}
	return (0);
}

void	ft_parser(void)
{
	t_cmd	*new;
	int		next;
	t_list	*list;
	char	**token;

	list = 0;
	next = 1;
	while (next)
	{
		next = ft_crtlst(&list);
		token = ft_crttkn_from_list(list);
		ft_lstclear(&list, ft_free_char);
		list = 0;
		if (!token)
			ft_exit("error");
		new = ft_cmdnew(token);
		if (!new)
			ft_exit("error");
		ft_cmdadd_back(&shell.cmd_table, new);
	}
}
	//	then is WORD
	//	if $
	//else if <				then return char* (stdout)
	//else if >				then return char* (stdin or stderr)
	//else if >>			then return char* (stdin end file)
	//else if $				then 
	//else if ;				then next cmd

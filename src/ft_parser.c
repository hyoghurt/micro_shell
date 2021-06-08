#include "minishell.h"

void	ft_exit_token(t_list **list)
{
	printf("exiiiiiiiiiit_tokkkkkkkkkkkkken\n");
	ft_lstclear(list, free);
	ft_exit("token", "error");
}

static void	ft_crt_lst(t_list **list);
static void	ft_new_token(t_list **list, char c);
static char	*ft_word(void);
static char	*ft_quote(char c);
static void	ft_redirect_std(t_list **list);
static char	*ft_file(void);

void	ft_parser(void)					//create shell.cmd_table  (is it token[0] token[1] ... | token[0] token[1] ...)
{
	t_cmd	*new;
	t_list	*list;
	char	**token;

	while (*shell.line && *shell.line != ';')
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
	}
}

static void	ft_crt_lst(t_list **list)			//create list separate word before '|'
{
	while (*shell.line && *shell.line != ';')
	{
		if (ft_strchr("\'\"", *shell.line))		//check quotes
			ft_new_token(list, *shell.line);	//create char*
		//else if (ft_strchr("<>", *shell.line))	//check redirect (<, >, <<)
		//	ft_redirect_std(list);
		else if (*shell.line == '|')
		{
			shell.line++;
			break ;
		}
		else if (!ft_strchr(" \t\n", *shell.line))
			ft_new_token(list, 0);				//create char*
		else
			shell.line++;
		//printf("*shell.line=[%c]\n", *shell.line);
	}
}

static void	ft_new_token(t_list **list, char c)		//create char*
{
	t_list	*new;
	char	*content;

	if (c)
		content = ft_quote(c);		//if have quote
	else
		content = ft_word();		//else
	if (!content)
		ft_exit_token(list);		//exit if error
	new = ft_lstnew(content);		//create list 
	if (!new)
		ft_exit_token(list);
	ft_lstadd_back(list, new);
}

static char	*ft_word(void)			// \n or \t word
{
	char	*start;
	char	*content;

	start = shell.line;
	while (!ft_strchr(" \t\n|;><\'\"$", *shell.line))
		shell.line++;
	content = ft_substr(start, 0, shell.line - start);
	return (content);
}

static char	*ft_quote(char c)		// " or ' word
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

/*
static void	ft_redirect_std(t_list **list)
{
	char	*file;
	char	*tmp;

	tmp = shell.line;

	file = ft_file();
	if (!file)
		ft_exit_token(list);

	if (*tmp == '<')
		shell.in_file = file;
	else if (*tmp == '>')
		shell.out_file = file;
}

static char	*ft_file(void)
{
	shell.line++;
	while (*shell.line)
	{
		if (ft_strchr("\'\"", *shell.line))
			return (ft_quote(*shell.line));
		else if (!ft_strchr(" \t\n", *shell.line))
			return (ft_word());
		shell.line++;
	}
}
*/


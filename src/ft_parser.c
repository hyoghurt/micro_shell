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

void	ft_parser(void)
{
	t_cmd	*new;
	t_list	*list;
	char	**token;

	while (*shell.line && *shell.line != ';')
	{
		//printf("shell.pars.sta=[%s]\n", shell.line);
		list = 0;
		ft_crt_lst(&list);
		token = ft_crttkn_from_list(list);
		ft_lstclear(&list, free);
		if (!token)
			ft_exit("error");
		new = ft_cmdnew(token);
		if (!new)
			ft_exit("error");
		ft_cmdadd_back(&shell.cmd_table, new);
		//printf("shell.pars.fin=[%s]\n", shell.line);
	}
}

static void	ft_crt_lst(t_list **list)
{
	while (*shell.line && *shell.line != ';')
	{
		if (ft_strchr("\'\"", *shell.line))
			ft_new_token(list, *shell.line);
		else if (ft_strchr("<>", *shell.line))
			ft_redirect_std(list);
		else if (*shell.line == '|')
		{
			shell.line++;
			break ;
		}
		else if (!ft_strchr(" \t\n", *shell.line))
			ft_new_token(list, 0);
		else
			shell.line++;
		//printf("*shell.line=[%c]\n", *shell.line);
	}
}

static void	ft_new_token(t_list **list, char c)
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

static char	*ft_word(void)
{
	char	*start;
	char	*content;

	start = shell.line;
	while (!ft_strchr(" \t\n|;><\'\"$", *shell.line))
		shell.line++;
	content = ft_substr(start, 0, shell.line - start);
	return (content);
}

static char	*ft_quote(char c)
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
	while(*shell.line)
	{
		if (ft_strchr("\'\"", *shell.line))
			return (ft_quote(*shell.line));
		else if (!ft_strchr(" \t\n", *shell.line))
			return (ft_word());
		shell.line++;
	}
}

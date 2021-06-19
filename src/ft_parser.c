#include "minishell.h"

void	ft_crt_lst(t_list **list);

void	ft_init_fd(void)
{
	g_shell.fd_in = 0;
	g_shell.fd_out = 1;
	g_shell.fd_in_file = 0;
	g_shell.fd_out_file = 0;
}

void	ft_parser(void)
{
	t_cmd	*new;
	t_list	*list;
	char	**token;

	while (*g_shell.line && *g_shell.line != ';')
	{
		token = 0;
		list = 0;
		ft_init_fd();
		ft_crt_lst(&list);
		token = ft_crt_arr_bi_from_list(list);
		if (list)
			ft_lstclear(&list, free);
		new = ft_cmdnew(token);
		if (!new)
		{
			ft_free_bi(token);
			ft_exit("minishell: parser: malloc", "error");
		}
		ft_cmdadd_back(&g_shell.cmd_table, new);
		while (*g_shell.line == '|'
			|| *g_shell.line == ' ' || *g_shell.line == '\t')
			g_shell.line++;
	}
}

void	ft_crt_lst(t_list **list)
{
	char	*string;
	t_list	*new;

	while (*g_shell.line && *g_shell.line != '|' && *g_shell.line != ';')
	{
		while (*g_shell.line == ' ' || *g_shell.line == '\t')
			g_shell.line++;
		if (*g_shell.line == '<' || *g_shell.line == '>')
			ft_parser_redirect();
		else if (*g_shell.line)
		{
			string = ft_crt_string(1);
			if (string)
			{
				new = ft_lstnew(string);
				if (!new)
					ft_exit(0, 0);
				ft_lstadd_back(list, new);
			}
		}
	}
}

char	*ft_crt_string(int f)
{
	char	*string;

	string = 0;
	while (*g_shell.line == ' ' || *g_shell.line == '\t')
		g_shell.line++;
	while (*g_shell.line && !ft_strchr(" \t<>;|", *g_shell.line))
	{
		if (*g_shell.line == '\\')
			ft_string_ecran(&string);
		else if (*g_shell.line == '\'' || *g_shell.line == '\"')
			ft_string_quote(&string, f);
		else if (*g_shell.line == '$'
			&& ft_check_set(*(g_shell.line + 1)) && f != 2)
			ft_string_env(&string);
		else if (*g_shell.line == '$' && *(g_shell.line + 1) == '?' && f != 2)
			ft_string_status(&string);
		else
			ft_string_word(&string);
	}
	return (string);
}

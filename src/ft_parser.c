#include "minishell.h"

void	ft_crt_lst(t_list **list);
void	ft_crt_token(t_list **list);

void	ft_parser(void)
{
	t_list	*list;

	while (*g_shell.line && *g_shell.line != ';')
	{
		list = 0;
		g_shell.fd_in = 0;
		g_shell.fd_out = 1;
		g_shell.fd_in_file = 0;
		g_shell.fd_out_file = 0;
		ft_crt_lst(&list);
		ft_crt_token(&list);
		ft_jump_space_and_pipe();
	}
}

void	ft_crt_lst(t_list **list)
{
	char	*string;
	t_list	*new;

	while (*g_shell.line && *g_shell.line != '|' && *g_shell.line != ';')
	{
		ft_jump_space();
		if (*g_shell.line == '<' || *g_shell.line == '>')
			ft_parser_redirect();
		else if (*g_shell.line && *g_shell.line != '|' && *g_shell.line != ';')
		{
			string = ft_crt_string(1);
			new = ft_lstnew(string);
			if (!new)
			{
				ft_lstclear(list, free);
				ft_exit("minishell: crt_list: malloc: ", "error");
			}
			ft_lstadd_back(list, new);
		}
	}
}

void	ft_crt_token(t_list **list)
{
	t_cmd	*new;
	char	**token;

	token = 0;
	if (*list)
	{
		token = ft_crt_arr_bi_from_list(*list);
		ft_lstclear(list, free);
		if (!token)
			ft_exit("minishell: parser: malloc: ", "error");
	}
	new = ft_cmdnew(token);
	if (!new)
	{
		ft_free_bi(token);
		ft_exit("minishell: parser: malloc: ", "error");
	}
	ft_cmdadd_back(&g_shell.cmd_table, new);
}

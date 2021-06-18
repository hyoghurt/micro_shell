#include "minishell.h"

void	ft_parser(void)
{
	t_cmd	*new;
	t_list	*list;
	char	**token;

	while (*shell.line && *shell.line != ';')
	{
		shell.fd_in = 0;
		shell.fd_out = 1;
		shell.fd_in_file = 0;
		shell.fd_out_file = 0;
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
	//debag_check_token();
	//exit(0);
}

void	ft_crt_lst(t_list **list)
{
	char	*string;
	t_list	*new;

	while (*shell.line && *shell.line != '|' && *shell.line != ';')
	{
		while (*shell.line == ' ' || *shell.line == '\t')
			shell.line++;
		if (*shell.line == '<' || *shell.line == '>')
			ft_parser_redirect();
		else if (*shell.line)
		{
			string = ft_crt_string();
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

char	*ft_crt_string(void)
{
	char	*string;

	string = 0;
	while (*shell.line == ' ' || *shell.line == '\t')
		shell.line++;
	while (*shell.line && !ft_strchr(" \t<>;|", *shell.line))
	{
		if (*shell.line == '\\')
			ft_string_ecran(&string);
		else if (*shell.line == '\'' || *shell.line == '\"')
			ft_string_quote(&string, *shell.line);
		else if (*shell.line == '$' && ft_check_set(*(shell.line + 1)))
			ft_string_env(&string);
		else if (*shell.line == '$' && *(shell.line + 1) == '?')
			ft_string_status(&string);
		else
			ft_string_word(&string);
	}
	return (string);
}

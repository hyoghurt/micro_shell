#include "minishell.h"

void	debag_check_shell_line(void)
{
	printf("\n\e[1;38;5;10mg_shell.line=\t[%s]\e[0m\n", g_shell.line);
}

void	debag_check_story(void)
{
	t_story	*tmp;

	tmp = g_shell.story;
	while (tmp)
	{
		printf("story=%s\n", tmp->str);
		tmp = tmp->next;
	}
}

void	debag_check_token(void)
{
	char	**s;
	t_cmd	*tmp;
	int		i;

	tmp = g_shell.cmd_table;
	while (tmp)
	{
		s = tmp->token;
		i = 0;
		while (s[i])
		{
			printf("\e[1;38;5;10mtoken[%d]=\t[%s]\e[0m", i, s[i]);
			printf("\t[fd_in]=%d ", tmp->fd_in);
			printf("[fd_in_file]=[%s]", tmp->fd_in_file);
			printf("\t[fd_out]=%d ", tmp->fd_out);
			printf("[fd_out_file]=[%s]", tmp->fd_out_file);
			printf("\n");
			i++;
		}
		printf("\n");
		tmp = tmp->next;
	}
}

void	debag_check_status(void)
{
	printf("\e[1;38;5;10m\np g_shell.cmd_table=%p\e[0m\n", g_shell.cmd_table);
	printf("\e[1;38;5;10mstatus=[%d]\e[0m\n", g_shell.status);
	printf("\e[1;38;5;10mexit_executor\e[0m\n");
}

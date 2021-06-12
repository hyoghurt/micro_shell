#include "minishell.h"

void	debag_check_shell_line(void)
{
	printf("\n\e[1;38;5;10mshell.line=\t[%s]\e[0m\n", shell.line);
}

void	debag_check_story(void)
{
	t_list	*tmp;

	tmp = shell.story;

	while (tmp)
	{
		printf("story=%s\n", tmp->content);
		tmp = tmp->next;
	}
}

void	debag_check_token(void)
{
	char	**s;
	t_cmd	*tmp;
	int		i;

	tmp = shell.cmd_table;
	while (tmp)
	{
		s = tmp->token;
		i = 0;
		while (s[i])
		{
			printf("\e[1;38;5;10mtoken[%d]=\t[%s]\e[0m\n", i, s[i]);
			i++;
		}
		printf("\n");
		tmp = tmp->next;
	}
}

void	debag_check_status(void)
{
	printf("\e[1;38;5;10m\np shell.cmd_table=%p\e[0m\n", shell.cmd_table);
	printf("\e[1;38;5;10mstatus=[%d]\e[0m\n", shell.status);
	printf("\e[1;38;5;10mexit_executor\e[0m\n");
}

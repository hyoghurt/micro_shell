#include "minishell.h"

void	ft_key_up(void)
{
	if (shell.fg_mv_story)						//if it no first push key
	{
		free(shell.move_story->str);
		shell.move_story->str = shell.line;
	}
	tputs(shell.key.rc, 1, ft_putint);		//restore cursor on start
	tputs(shell.key.cd, 1, ft_putint);		//clear all after cursor
	shell.fg_mv_story = 1;
	if (shell.move_story->next)
		shell.move_story = shell.move_story->next;
	shell.line = ft_strdup(shell.move_story->str);
	ft_putstr_fd(shell.line, 1);
}

void	ft_key_down(void)
{
	if (shell.fg_mv_story)
	{
		free(shell.move_story->str);
		shell.move_story->str = shell.line;
	}
	tputs(shell.key.rc, 1, ft_putint);		//restore cursor on start
	tputs(shell.key.cd, 1, ft_putint);		//clear all after cursor
	shell.fg_mv_story = 1;
	if (shell.move_story->back)
		shell.move_story = shell.move_story->back;
	shell.line = ft_strdup(shell.move_story->str);
	ft_putstr_fd(shell.line, 1);
}

void	ft_key_backsp(void)
{
	size_t	i;

	//ft_putstr_fd("one\n", 1);
	tputs(shell.key.rc, 1, ft_putint);		//restore cursor on start
	tputs(shell.key.cd, 1, ft_putint);		//clear all after cursor

	i = ft_strlen(shell.line);
	shell.line[i - 1] = '\0';				//change shell.line
	ft_putstr_fd(shell.line, 1);
}

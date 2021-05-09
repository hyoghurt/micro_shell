#include "minishell.h"

void	ft_key_up(void)
{
	if (shell.fg_mv_story)
	{
		free(shell.move_story->str);
		shell.move_story->str = shell.line;
	}
	tputs(shell.key.dl, 1, ft_putint);		//clear line
	ft_set_prompt();					//set prompt
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
	tputs(shell.key.dl, 1, ft_putint);		//clear line
	ft_set_prompt();					//set prompt
	shell.fg_mv_story = 1;
	if (shell.move_story->back)
		shell.move_story = shell.move_story->back;
	shell.line = ft_strdup(shell.move_story->str);
	ft_putstr_fd(shell.line, 1);
}

void	ft_key_backsp(void)
{
	size_t	i;

	tputs(shell.key.rc, 1, ft_putint);
	tputs(shell.key.cd, 1, ft_putint);

	i = ft_strlen(shell.line);
	shell.line[i - 1] = '\0';
	ft_putstr_fd(shell.line, 1);
}

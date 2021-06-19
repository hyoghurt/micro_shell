#include "minishell.h"

void	ft_key_up(void)
{
	if (g_shell.fg_mv_story)
	{
		free(g_shell.move_story->str);
		g_shell.move_story->str = g_shell.line;
	}
	tputs(g_shell.key.rc, 1, ft_putint);
	tputs(g_shell.key.cd, 1, ft_putint);
	g_shell.fg_mv_story = 1;
	if (g_shell.move_story->next)
		g_shell.move_story = g_shell.move_story->next;
	g_shell.line = ft_strdup(g_shell.move_story->str);
	ft_putstr_fd(g_shell.line, 1);
}

void	ft_key_down(void)
{
	if (g_shell.fg_mv_story)
	{
		free(g_shell.move_story->str);
		g_shell.move_story->str = g_shell.line;
	}
	tputs(g_shell.key.rc, 1, ft_putint);
	tputs(g_shell.key.cd, 1, ft_putint);
	g_shell.fg_mv_story = 1;
	if (g_shell.move_story->back)
		g_shell.move_story = g_shell.move_story->back;
	g_shell.line = ft_strdup(g_shell.move_story->str);
	ft_putstr_fd(g_shell.line, 1);
}

void	ft_key_backsp(char *s)
{
	size_t	i;

	tputs(g_shell.key.rc, 1, ft_putint);
	tputs(g_shell.key.cd, 1, ft_putint);
	i = ft_strlen(s);
	s[i - 1] = '\0';
	ft_putstr_fd(s, 1);
}

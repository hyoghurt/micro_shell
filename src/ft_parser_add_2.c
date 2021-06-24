#include "minishell.h"

void	ft_jump_space_and_pipe(void)
{
	while (*g_shell.line == '|' || *g_shell.line == ' ' || *g_shell.line == '\t')
		g_shell.line++;
}

void	ft_jump_space(void)
{
	while (*g_shell.line == ' ' || *g_shell.line == '\t')
		g_shell.line++;
}

int	ft_check_set(char c1, char c2)
{
	if (c1 == '$' && ft_check_start_set(c2))
		return (1);
	return (0);
}

int	ft_check_status(char c1, char c2)
{
	if (c1 == '$' && c2 == '?')
		return (1);
	return (0);
}

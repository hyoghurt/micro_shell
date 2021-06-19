#include "minishell.h"

void	ft_init_termios(void);
void	ft_init_add_story(void);

void	ft_start(void)
{
	g_shell.line = 0;
	ft_init_string(&g_shell.line);
	ft_init_add_story();
}

void	ft_init_add_story(void)
{
	t_story	*new;

	new = ft_story_new(g_shell.line);
	if (!new)
	{
		free(g_shell.line);
		ft_exit("minishell: story_new: malloc: ", "error");
	}
	g_shell.fg_mv_story = 0;
	g_shell.move_story = new;
	ft_story_add_front(&g_shell.story, new);
}

void	ft_init_termios(void)
{
	struct termios	termios_temp;

	if (tcgetattr(0, &termios_temp) != 0)
		ft_exit("minishell: init_termios: tcgetattr: ", "error");
	termios_temp.c_lflag &= ~(ECHO | ICANON);
	termios_temp.c_cc[VMIN] = 1;
	termios_temp.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSANOW, &termios_temp) != 0)
		ft_exit("minishell: init_termios: tcsetattr: ", "error");
}

int	ft_set_prompt(void)
{
	ft_putstr_fd ("\033[1;48;5;58m", 1);
	if (g_shell.user)
		ft_putstr_fd (g_shell.user, 1);
	else
		ft_putstr_fd ("USER", 1);
	ft_putstr_fd (" > \033[0m", 1);
	tputs(g_shell.key.sc, 1, ft_putint);
	return (0);
}

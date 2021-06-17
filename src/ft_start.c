#include "minishell.h"

static void	ft_init_termios(void);
static void	ft_init_add_story(void);
static int	ft_set_prompt(void);

void	ft_start(void)
{
	shell.line = 0;
	ft_init_termios();
	ft_init_shell_line();
	ft_init_add_story();
	ft_set_prompt();
}

static void	ft_init_add_story(void)
{
	t_story	*new;

	new = ft_story_new(shell.line);
	if (!new)
	{
		free(shell.line);
		ft_exit("minishell: story_new: malloc: ", "error");
	}
	shell.fg_mv_story = 0;
	shell.move_story = new;
	ft_story_add_front(&shell.story, new);
}

static void	ft_init_termios(void)
{
	struct termios	termios_temp;

	if (tcgetattr(0, &termios_temp) != 0)
		ft_exit("minishell: init_termios: tcgetattr: ", "error");
	termios_temp.c_lflag &= ~(ECHO|ICANON);
	termios_temp.c_cc[VMIN] = 1;
	termios_temp.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSANOW, &termios_temp) != 0)
		ft_exit("minishell: init_termios: tcsetattr: ", "error");
}

static int	ft_set_prompt(void)
{
	ft_putstr_fd ("\033[1;48;5;58m", 1);
	if (shell.user)
		ft_putstr_fd (shell.user, 1);
	else
		ft_putstr_fd ("USER", 1);
	ft_putstr_fd (" > \033[0m", 1);
	tputs(shell.key.sc, 1, ft_putint);	//save cursor position (need for backspace and move story)
	return (0);
}

#include "minishell.h"

int	ft_set_prompt(void)
{
	char	*user;

	//user = getenv("USER");
	user = "USER";
	write (1, "\033[1;48;5;58m", strlen("\033[1;48;5;58m"));
	if (user)
		write (1, user, strlen(user));
	write (1, " > ", 3);
	write (1, "\033[0m", strlen("\033[0m"));
	return (0);
}

int	ft_init_termtype(void)
{
	struct termios	temp;
	char			*termtype;
	int				init;
	char			term_buffer[2048];

	termtype = getenv("TERM");
	if (!termtype)
		return (1);
	init = tgetent(term_buffer, termtype);
	if (init < 0)
	{
		printf("Could not access the termcap data base.\n");
		return (1);
	}
	if (init == 0)
	{
		printf("Terminal type `%s' is not defined.\n", termtype);
		return (1);
	}
	return (0);
}

int	ft_init_termios(void)
{
	struct termios termios_temp;
	int r;

	if (ft_init_termtype())
		ft_exit("err_tcgetattr");
	if (tcgetattr(0, &termios_temp) != 0)
		ft_exit("err_tcgetattr");
	ft_memcpy(&shell.termios_p, &termios_temp, sizeof(termios_temp));
	termios_temp.c_lflag &= ~(ECHO|ICANON);
	termios_temp.c_cc[VMIN] = 1;
	termios_temp.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSANOW, &termios_temp) != 0)
		ft_exit("error");
	return (0);
}

void	ft_init_struct(void)
{
	shell.cache_bi = ft_calloc(BUF_SIZE, 1);
	if (!shell.cache_bi)
		ft_exit("error");
	shell.line = 0;
	shell.cmd_table = 0;
	shell.out_file = 0;
	shell.inp_file = 0;
	shell.err_file = 0;
}

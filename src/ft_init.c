#include "minishell.h"

void	ft_init_struct(void);
void	ft_init_termios(void);
void	ft_init_termtype(void);
void	ft_init_set(char **envp);

void	ft_init(char **envp)
{
	signal(SIGINT, ft_sig_ctrl_c);				//signal Ctrl-C

	ft_init_struct();							//init struct shell (global varible)
	ft_init_termios();							//init terminal
	ft_init_set(envp);							//copy envp in shell.set
}

void	ft_init_struct(void)
{
	shell.cache_bi = ft_calloc(BUF_SIZE, 1);	//   !!!!!   write do konza
	if (!shell.cache_bi)
		ft_exit("malloc", "error");
	shell.line = 0;
	shell.cmd_table = 0;
	shell.out_file = 0;
	shell.in_file = 0;
	shell.err_file = 0;
	shell.status = 0;
	shell.set = 0;
	shell.pathtkn = 0;
}

void	ft_init_termios(void)
{
	struct termios	termios_temp;

	ft_init_termtype();
	if (tcgetattr(0, &termios_temp) != 0)
		ft_exit("tcgetattr", "err_tcgetattr");
	ft_memcpy(&shell.termios_p, &termios_temp, sizeof(termios_temp));
	termios_temp.c_lflag &= ~(ECHO|ICANON);
	termios_temp.c_cc[VMIN] = 1;
	termios_temp.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSANOW, &termios_temp) != 0)
		ft_exit("tcgetattr", "error");
}

void	ft_init_termtype(void)
{
	char	*termtype;
	char	term_buffer[2048];

	termtype = getenv("TERM");
	if (!termtype)
		ft_exit("termtype", "err_tcgetattr");
	if (tgetent(term_buffer, termtype) <= 0)
		ft_exit("tgetent", "err_tcgetattr");
}

void	ft_init_set(char **envp)
{
	size_t	size;
	char	**set;

	size = 0;
	if (envp)
		size = ft_array_len(envp);
	set = (char**)malloc((size + 1) * sizeof(char*));
	if (!set)
		ft_exit("malloc", "error");
	shell.set = ft_cpy_array_bi(set, envp);
	if (!shell.set)
		ft_exit("malloc", "error");
}

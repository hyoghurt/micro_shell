#include "minishell.h"

void	ft_init_struct(void);
void	ft_init_termios(void);
void	ft_init_termtype(void);
void	ft_init_set(char **envp);
void	ft_init_key(void);

void	ft_init(char **envp)
{
	//signal(SIGINT, ft_sig_ctrl_c);				//signal Ctrl-C
	signal(SIGINT, SIG_IGN);				//signal Ctrl-C

	ft_init_struct();							//init struct shell (global varible)
	ft_init_termios();							//init terminal
	ft_init_key();
	ft_init_set(envp);							//copy envp in shell.set
}

void	ft_init_struct(void)
{
	shell.story = 0;
	shell.line = 0;
	shell.cmd_table = 0;
	shell.out_file = 0;
	shell.in_file = 0;
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

void	ft_init_shell_line(void)
{
	size_t	len;
	size_t	rest;
	size_t	whole;
	char	*tmp;

	if (shell.line)
	{
		len = ft_strlen(shell.line);
		rest = len % BUF_SIZE;
		whole = len / BUF_SIZE;
		if (whole >= 1 && rest == 2)
		{
			tmp = (char*)malloc((whole + 2) * BUF_SIZE);
			ft_strlcpy(tmp, shell.line, len + 1);
			free(shell.line);
			shell.line = tmp;
		}
	}
	else
		shell.line = ft_calloc(1, (BUF_SIZE * 2));
	if (!shell.line)
		ft_exit("malloc in init_shell_line", "error");
}

void	ft_init_key(void)
{
	shell.key.dl		= tgetstr("dl", 0);		//clear line
	shell.key.dc		= tgetstr("dc", 0);		//kursor left
	//shell.key.down		= tgetstr("do", 0);
	//shell.down		= tgetstr("kd", 0);
	shell.key.down		= "\033[B";
	//shell.right		= tgetstr("nd", 0);
	//shell.left		= tgetstr("le", 0);
	//shell.left		= tgetstr("kl", 0);
	//shell.left		= "\033[D";
	shell.key.up		= tgetstr("up", 0);
	shell.key.backsp	= tgetstr("kb", 0);
	//shell.key.co		= tgetnum("co");
	//shell.key.li		= tgetnum("li");
	shell.key.rc		= tgetstr("rc", 0);
	shell.key.cd		= tgetstr("cd", 0);
	shell.key.sc		= tgetstr("sc", 0);
	//if (!shell.dl || !shell.down || !shell.up || !shell.backsp)	//write
	//	ft_exit ("tgetstr", "error");
}

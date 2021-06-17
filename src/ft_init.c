#include "minishell.h"

void	ft_init_struct(void);
void	ft_init_termtype(void);
void	ft_init_set(char **envp);
void	ft_init_key(void);

void	ft_init(char **envp)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_sig_ctrl_c);

	ft_init_struct();
	ft_init_termtype();
	if (tcgetattr(0, &shell.termios_p) != 0)
		ft_exit("minishell: init: tcgetattr: ", "err_tcgetattr");
	ft_init_key();
	ft_init_set(envp);
	shell.user = getenv("USER");
}

void	ft_init_struct(void)
{
	shell.story = 0;
	shell.line = 0;
	shell.cmd_table = 0;
	shell.status = 0;
	shell.set = 0;
	shell.pathtkn = 0;
	shell.pid = 0;
}

void	ft_init_termtype(void)
{
	char	*termtype;
	char	term_buffer[2048];

	termtype = getenv("TERM");
	if (!termtype)
		ft_exit("minishell: termtype", "err_tcgetattr");
	if (tgetent(term_buffer, termtype) <= 0)
		ft_exit("minishell: tgetent", "err_tcgetattr");
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
		ft_exit("minishell: init_set: malloc: ", "error");
	shell.set = ft_cpy_array_bi(set, envp);
	if (!shell.set)
		ft_exit("minishell: init_set: malloc: ", "error");
}

void	ft_init_key(void)
{
	shell.key.down = "\033[B";
	shell.key.up = tgetstr("up", 0);
	shell.key.rc = tgetstr("rc", 0);		//restore "sc" position
	shell.key.sc = tgetstr("sc", 0);		//save cursor position
	shell.key.cd = tgetstr("cd", 0);		//clear before cursor
	if (!shell.key.down || !shell.key.up || !shell.key.rc 
			|| !shell.key.sc || !shell.key.cd)
		ft_exit ("minishell: init_key: ", "error");
}

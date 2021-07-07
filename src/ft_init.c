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
	signal(SIGQUIT, ft_sig_ctrl_c);
	ft_init_struct();
	ft_init_termtype();
	if (tcgetattr(0, &g_shell.termios_p) != 0)
		ft_exit("minishell: init: tcgetattr: ", "err_tcgetattr");
	ft_init_key();
	ft_init_set(envp);
	g_shell.user = getenv("USER");
}

void	ft_init_struct(void)
{
	g_shell.story = 0;
	g_shell.line = 0;
	g_shell.cmd_table = 0;
	g_shell.status = 0;
	g_shell.exit = 0;
	g_shell.set = 0;
	g_shell.pathtkn = 0;
	g_shell.pid = 0;
	g_shell.fd_in = 0;
	g_shell.fd_out = 1;
	g_shell.fd_in_file = 0;
	g_shell.fd_out_file = 0;
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
	set = (char **)malloc((size + 1) * sizeof(char *));
	if (!set)
		ft_exit("minishell: init_set: malloc: ", "error");
	g_shell.set = ft_cpy_array_bi(set, envp);
	if (!g_shell.set)
		ft_exit("minishell: init_set: malloc: ", "error");
}

void	ft_init_key(void)
{
	g_shell.key.down = "\033[B";
	g_shell.key.up = tgetstr("up", 0);
	g_shell.key.rc = tgetstr("rc", 0);
	g_shell.key.sc = tgetstr("sc", 0);
	g_shell.key.cd = tgetstr("cd", 0);
	if (!g_shell.key.up || !g_shell.key.rc
		|| !g_shell.key.sc || !g_shell.key.cd)
		ft_exit ("minishell: init_key: ", "error");
}

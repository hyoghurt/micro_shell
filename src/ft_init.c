#include "minishell.h"

void	ft_init_struct(void);
void	ft_init_termios(void);
void	ft_init_termtype(void);
void	ft_init_set(char **envp);
void	ft_init_key(void);

void		ft_sig_ctrl_c(int sig)
{
	printf("in c-c\n");
}

void	ft_init(char **envp)
{
	signal(SIGINT, SIG_IGN);				//signal Ctrl-C
	signal(SIGINT, ft_sig_ctrl_c);		//signal Ctrl-C

	ft_init_struct();						//init struct shell (global varible)
	ft_init_set(envp);						//copy envp in shell.set
}

void	ft_init_struct(void)		//init struct
{
	shell.story = 0;
	shell.line = 0;
	shell.cmd_table = 0;
	shell.status = 0;
	shell.set = 0;
	shell.pathtkn = 0;
	shell.pid = 0;
}

void	ft_init_set(char **envp)	//copy envp in shell.set
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

void	ft_init_shell_line(void)   //do recalloc shell.line
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

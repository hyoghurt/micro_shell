#include "minishell.h"

int		ft_print_error(void)
{
	char	*string;

	string = strerror(errno);
	if (string)
		write (2, string, ft_strlen(string));
	return (1);
}

void	ft_free_bi(char **s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		printf("token_0=%ld\n", i);
		free(s[i]);
		i++;
	}
	free(s);
}

void	ft_cmdclear(t_cmd **cmd)
{
	t_cmd	*tmp;
	int		i;

	i = 0;
	while (*cmd)
	{
		tmp = *cmd;
		*cmd = (*cmd)->next;
		printf("start_free_bi\n");
		ft_free_bi(tmp->token);
		printf("finish_free_bi\n");
		free(tmp);
		tmp = 0;
	}
}

void	ft_free_shell(void)
{
	if (shell.cache_bi)
		ft_free_bi(shell.cache_bi);
	if (shell.cmd_table)
		ft_cmdclear(&shell.cmd_table);
	if (shell.out_file)
		free(shell.out_file);
	if (shell.inp_file)
		free(shell.inp_file);
	if (shell.err_file)
		free(shell.err_file);
}

int		ft_exit(char *s)
{
	int	ret;

	ft_free_shell();
	ret = 0;
	if (s)
	{
		ret = ft_print_error();
		if (ft_strncmp(s, "err_tcgetattr", 13))
			exit (1);
	}
	if (tcsetattr(0, TCSANOW, &shell.termios_p) != 0)
		ret = ft_print_error();
	write(1, "exit\n", 5);
	exit (ret);
}

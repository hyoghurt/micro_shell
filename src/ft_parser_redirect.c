#include "minishell.h"

void	ft_redirect_in(void);
void	ft_redirect_in_2(void);
void	ft_redirect_out(void);
void	ft_redirect_out_2(void);

void	ft_parser_redirect(void)
{
	char	*string;

	if (*shell.line == '<')
	{
		shell.line++;
		if (*shell.line == '<')
			ft_redirect_in_2();
		else
			ft_redirect_in();
	}
	else
	{
		shell.line++;
		if (*shell.line == '>')
			ft_redirect_out_2();
		else
			ft_redirect_out();
	}
}

void	ft_redirect_in(void)
{
	char	*string;

	string = ft_crt_string();
	if (shell.fd_in >= 0)
	{
		if (shell.fd_in != 0)
		{
			close(shell.fd_in);
			if (shell.fd_in_file)
			{
				free(shell.fd_in_file);
				shell.fd_in_file = 0;
			}
		}
		shell.fd_in = open(string, O_RDONLY, 0644);
		shell.fd_in_file = string;
	}
	else
		free(string);
}

void	ft_redirect_in_2(void)
{
	char	*string;
	char	*s;

	shell.line++;
	string = ft_crt_string();
	if (shell.fd_in >= 0)
	{
		if (shell.fd_in != 0)
		{
			close(shell.fd_in);
			if (shell.fd_in_file)
			{
				free(shell.fd_in_file);
				shell.fd_in_file = 0;
			}
		}
		shell.fd_in = open(REDIR_MY, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		while (1)
		{
			s = readline("\033[1;48;5;20m > \033[0m");
			if (!s)
			{
				printf("on tut\n");
				free(string);
				close(shell.fd_in);
				shell.fd_in = open(REDIR_MY, O_RDONLY, 0644);
				//shell.fd_in = 0;
				return ;
			}
			if (!ft_strncmp(string, s, ft_strlen(string) + 1))
			{
				free(s);
				free(string);
				break ;
			}
			ft_putstr_fd(s, shell.fd_in);
			ft_putstr_fd("\n", shell.fd_in);
			free(s);
		}
		close(shell.fd_in);
		shell.fd_in = open(REDIR_MY, O_RDONLY, 0644);
	}
	else
		free(string);
}

void	ft_redirect_out(void)
{
	char	*string;

	string = ft_crt_string();
	if (shell.fd_out >= 1)
	{
		if (shell.fd_out != 1)
		{
			close(shell.fd_out);
			free(shell.fd_out_file);
		}
		shell.fd_out = open(string, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		shell.fd_out_file = string;
	}
	else
		free(string);
}

void	ft_redirect_out_2(void)
{
	char	*string;

	shell.line++;
	string = ft_crt_string();
	if (shell.fd_out >= 1)
	{
		if (shell.fd_out != 1)
		{
			close(shell.fd_out);
			free(shell.fd_out_file);
		}
		shell.fd_out = open(string, O_WRONLY | O_CREAT | O_APPEND, 0644);
		shell.fd_out_file = string;
	}
	else
		free(string);
}

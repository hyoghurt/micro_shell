#include "minishell.h"

void	ft_redirect_in(void);
void	ft_redirect_in_2(void);
void	ft_redirect_out(void);
void	ft_redirect_out_2(void);

void	ft_parser_redirect(void)
{
	if (*g_shell.line == '<')
	{
		g_shell.line++;
		if (*g_shell.line == '<')
			ft_redirect_in_2();
		else
			ft_redirect_in();
	}
	else
	{
		g_shell.line++;
		if (*g_shell.line == '>')
			ft_redirect_out_2();
		else
			ft_redirect_out();
	}
}

void	ft_redirect_in(void)
{
	char	*string;

	string = ft_crt_string(1);
	if (g_shell.fd_in >= 0)
	{
		if (g_shell.fd_in != 0)
		{
			close(g_shell.fd_in);
			if (g_shell.fd_in_file)
			{
				free(g_shell.fd_in_file);
				g_shell.fd_in_file = 0;
			}
		}
		g_shell.fd_in = open(string, O_RDONLY, 0644);
		g_shell.fd_in_file = string;
	}
	else
		free(string);
}

void	ft_redirect_in_2(void)
{
	char	*string;

	string = 0;
	g_shell.line++;
	string = ft_crt_string(2);
	if (g_shell.fd_in >= 0)
	{
		if (g_shell.fd_in != 0)
		{
			close(g_shell.fd_in);
			if (g_shell.fd_in_file)
			{
				free(g_shell.fd_in_file);
				g_shell.fd_in_file = 0;
			}
		}
		ft_redir_content(string);
	}
	free(string);
}

void	ft_redirect_out(void)
{
	char	*string;

	string = ft_crt_string(1);
	if (g_shell.fd_out >= 1)
	{
		if (g_shell.fd_out != 1)
		{
			close(g_shell.fd_out);
			free(g_shell.fd_out_file);
		}
		g_shell.fd_out = open(string, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		g_shell.fd_out_file = string;
	}
	else
		free(string);
}

void	ft_redirect_out_2(void)
{
	char	*string;

	g_shell.line++;
	string = ft_crt_string(1);
	if (g_shell.fd_out >= 1)
	{
		if (g_shell.fd_out != 1)
		{
			close(g_shell.fd_out);
			free(g_shell.fd_out_file);
		}
		g_shell.fd_out = open(string, O_WRONLY | O_CREAT | O_APPEND, 0644);
		g_shell.fd_out_file = string;
	}
	else
		free(string);
}

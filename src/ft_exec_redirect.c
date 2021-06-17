#include "minishell.h"

int	find_redirect_file(t_cmd *cmd)
{
	if (cmd->fd_in < 0)
	{
		ft_print_string("minishell", cmd->fd_in_file, strerror(errno));
		return (1);
	}
	if (cmd->fd_out < 0)
	{
		ft_print_string("minishell", cmd->fd_out_file, strerror(errno));
		return (1);
	}
	return (0);
}

/*
int	find_redirect_file(t_cmd *cmd)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	while (cmd->token[i])
	{
		if (!ft_strncmp(cmd->token[i], "<", 2))
		{
			if (cmd->fd_in != 0)
				close(cmd->fd_in);
			cmd->fd_in = open(cmd->token[i + 1], O_RDONLY, 0644);
			if (cmd->fd_in < 0)
			{
				ft_print_string("minishell", cmd->token[i + 1], strerror(errno));
				return (1);
			}
			free(cmd->token[i + 1]);
			free(cmd->token[i]);
			i += 2;
		}
		else if (!ft_strncmp(cmd->token[i], ">", 2))
		{
			if (cmd->fd_out != 1)
				close(cmd->fd_out);
			cmd->fd_out = open(cmd->token[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (cmd->fd_out < 0)
			{
				ft_print_string("minishell", cmd->token[i + 1], strerror(errno));
				return (1);
			}
			free(cmd->token[i + 1]);
			free(cmd->token[i]);
			i += 2;
		}
		else if (!ft_strncmp(cmd->token[i], ">>", 3))
		{
			if (cmd->fd_out != 1)
				close(cmd->fd_out);
			cmd->fd_out = open(cmd->token[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (cmd->fd_out < 0)
			{
				ft_print_string("minishell", cmd->token[i + 1], strerror(errno));
				return (1);
			}
			free(cmd->token[i + 1]);
			free(cmd->token[i]);
			i += 2;
		}
		else
			cmd->token[j++] = cmd->token[i++];
	}
	cmd->token[j] = 0;
	return (0);
}
*/

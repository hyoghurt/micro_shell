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

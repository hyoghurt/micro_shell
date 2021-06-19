#include "minishell.h"

t_cmd	*ft_cmdnew(char	**token)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (0);
	new->token = token;
	new->next = 0;
	new->fd_in = g_shell.fd_in;
	new->fd_out = g_shell.fd_out;
	new->fd_in_file = g_shell.fd_in_file;
	new->fd_out_file = g_shell.fd_out_file;
	return (new);
}

void	ft_cmdadd_back(t_cmd **cmd, t_cmd *new)
{
	t_cmd	*tmp;

	tmp = *cmd;
	if (!tmp)
		*cmd = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	ft_cmdclear(t_cmd **cmd)
{
	t_cmd	*tmp;
	t_cmd	*bg;

	tmp = *cmd;
	while (tmp)
	{
		bg = tmp;
		tmp = tmp->next;
		if (bg->token)
			ft_free_bi(bg->token);
		if (bg->fd_in_file)
			free(bg->fd_in_file);
		if (bg->fd_out_file)
			free(bg->fd_out_file);
		free(bg);
	}
	*cmd = 0;
}

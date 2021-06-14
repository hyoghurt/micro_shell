#include "minishell.h"

t_cmd	*ft_cmdnew(char	**token)
{
	t_cmd	*new;

	if (!token)
		return (0);
	new = (t_cmd*)malloc(sizeof(t_cmd));
	if (!new)
		return (0);
	new->token = token;
	new->next = 0;
	new->fd_in = 0;
	new->fd_out = 1;
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
		while(tmp->next)
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
		ft_free_bi(bg->token);
		free(bg);
	}
	*cmd = 0;
}

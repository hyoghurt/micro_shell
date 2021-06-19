#include "minishell.h"

t_pid	*ft_pidnew(int n)
{
	t_pid	*new;

	new = (t_pid *)malloc(sizeof(t_pid));
	if (!new)
		return (0);
	new->pid = n;
	new->next = 0;
	return (new);
}

void	ft_addpid_back(t_pid **pid, t_pid *new)
{
	t_pid	*tmp;

	tmp = *pid;
	if (!tmp)
		*pid = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	ft_pidclear(t_pid **pid)
{
	t_pid	*bg;

	while (*pid)
	{
		bg = *pid;
		*pid = (*pid)->next;
		free(bg);
	}
	*pid = 0;
}

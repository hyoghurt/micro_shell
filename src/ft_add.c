#include "minishell.h"

int		ft_putint(int c)
{
	write(1, &c, 1);
}

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
	return (new);
}
		
void	ft_cmdadd_back(t_cmd **cmd, t_cmd *new)
{
	if (!(*cmd))
		*cmd = new;
	else
	{
		while((*cmd)->next)
			*cmd = (*cmd)->next;
		(*cmd)->next = new;
	}
}

void	ft_free_char(void *s)
{
	free(s);
}

char	**ft_crttkn_from_list(t_list *list)
{
	size_t	size;
	char	**tokens;
	size_t	i;

	size = ft_lstsize(list);
	tokens = (char**)malloc(sizeof(char*) * size);
	if (!tokens)
		return (0);		//write error
	i = 0;
	while (i < size)
	{
		tokens[i] = ft_strdup(list->content);
		if (!tokens[i])
			return (0);	//write error
		list = list->next;
		i++;
	}
	tokens[i] = 0;
	return (tokens);
}

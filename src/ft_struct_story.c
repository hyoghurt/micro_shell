#include "minishell.h"

t_story	*ft_story_new(char *str)
{
	t_story	*new;

	if (!str)
		return (0);
	new = malloc(sizeof(t_story));
	if (!new)
		return (0);
	new->str = str;
	new->next = 0;
	new->back = 0;
	return (new);
}

void	ft_story_add_front(t_story **story, t_story *new)
{
	if (!(*story))
		*story = new;
	else
	{
		new->next = *story;
		(*story)->back = new;
		*story = new;
	}
}

void	ft_story_del_front(t_story **story)
{
	t_story		*tmp;
	t_story		*bg;

	tmp = *story;
	if (tmp)
	{
		bg = tmp;
		tmp = tmp->next;
		if (bg->str)
			free(bg->str);
		free(bg);
		tmp->back = 0;
		*story = tmp;
	}
}

void	ft_story_add_back(t_story **story, t_story *new)
{
	t_story		*tmp;

	if (!(*story))
		*story = new;
	else
	{
		tmp = *story;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->back = tmp;
	}
}

void	ft_story_clear(t_story **story)
{
	t_story		*tmp;
	t_story		*bg;

	tmp = *story;
	while (tmp)
	{
		bg = tmp;
		tmp = tmp->next;
		if (bg->str)
			free(bg->str);
		free(bg);
	}
	*story = 0;
}

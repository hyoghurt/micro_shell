#include "minishell.h"

static t_list	*ft_crt_path_list(char *path, char **cmd);
static char		*ft_str_path(char **path, char **cmd);
static char		*ft_pathname(t_list **list);

char	*ft_path_token(char **cmd)
{
	struct stat	buf;
	char		*path;
	t_list		*path_list;

	if (stat(cmd[0], &buf) == 0)
	{
		path = ft_strdup(cmd[0]);
		if (!path)
			ft_exit("minishell: path_token: malloc: ", "error");
		return (path);
	}
	path = ft_getset("PATH");
	if (!path)
		return (path);
	path_list = ft_crt_path_list(path, cmd);
	free(path);
	if (!path_list)
		ft_exit("minishell: path_list: malloc: ", "error");
	return (ft_pathname(&path_list));
}

static t_list	*ft_crt_path_list(char *path, char **cmd)
{
	t_list	*result;
	t_list	*new;
	char	*str;

	result = 0;
	while (1)
	{
		path = ft_strchr(path, '/');
		if (!path)
			break ;
		str = ft_str_path(&path, cmd);
		new = ft_lstnew(str);
		if (!new)
			ft_exit("minishell: path_list: malloc: ", "error");
		ft_lstadd_back(&result, new);
	}
	return (result);
}

static char	*ft_str_path(char **path, char **cmd)
{
	size_t	i;
	size_t	len;
	char	*result;
	char	*str;

	len = ft_strlen(cmd[0]);
	str = *path;
	i = 0;
	while (str[i] && str[i] != ':')
		i++;
	*path = &str[i];
	result = ft_calloc((i + len + 2), 1);
	if (!result)
		ft_exit("minishell: path_str: malloc: ", "error");
	ft_strlcat(result, str, i + 1);
	ft_strlcat(result, "/", i + 2);
	ft_strlcat(result, cmd[0], len + i + 2);
	return (result);
}

static char	*ft_pathname(t_list **list)
{
	struct stat	buf;
	t_list		*path_list;
	char		*pathname;

	path_list = *list;
	while (path_list)
	{
		if (stat((char *)path_list->content, &buf) == 0)
		{
			pathname = ft_strdup((char *)path_list->content);
			if (!pathname)
				ft_exit("minishell: pathname: malloc: ", "error");
			ft_lstclear(list, free);
			return (pathname);
		}
		path_list = path_list->next;
	}
	ft_lstclear(list, free);
	return (0);
}

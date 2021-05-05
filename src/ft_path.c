#include "minishell.h"

char	*ft_str_path(char **path)
{
	size_t	i;
	char	*result;
	char	*str;
	size_t	len;

	len = ft_strlen(shell.cmd_table->token[0]);
	str = *path;
	i = 0;
	while (str[i] != ':' && str[i])
		i++;
	*path = &str[i];
	result = (char*)malloc(i + len + 2);
	if (!result)
		return (0);
	ft_memcpy(result, str, i);
	result[i] = '/';
	ft_memcpy((result + i + 1), shell.cmd_table->token[0], len);
	result[i + len + 1] = 0;
	return (result);
}

t_list	*ft_crt_path_list(char *path)
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
		str = ft_str_path(&path);
		if (!str)
			ft_exit("error");	//write errror
		new = ft_lstnew(str);
		if (!new)
			ft_exit("error");	//write error
		ft_lstadd_back(&result, new);
	}
	return (result);
}

char	*ft_pathname(t_list **list)
{
	struct stat	buf;
	t_list		*path_list;
	char		*pathname;

	path_list = *list;
	while (path_list)
	{
		if (stat((char*)path_list->content, &buf) == 0)
		{
			pathname = ft_strdup((char*)path_list->content);
			ft_lstclear(list, ft_free_char);
			return (pathname);
		}
		path_list = path_list->next;
	}
	ft_lstclear(list, ft_free_char);
	return (0);
}

char	*ft_path_token(void)
{
	struct stat	buf;
	char		*path;
	t_list		*path_list;

	if (stat(shell.cmd_table->token[0], &buf) == 0)
		return (shell.cmd_table->token[0]);

	path = ft_getset("PATH");
	if (!path)
		ft_exit("error");	//write

	path_list = ft_crt_path_list(path);
	free(path);
	if (!path_list)
		ft_exit("error");	//write

	return (ft_pathname(&path_list));
}

#include "minishell.h"

t_list	*ft_crt_path_list(char *path, t_cmd *cmd);
char	*ft_str_path(char **path, t_cmd *cmd);
char	*ft_pathname(t_list **list);

char	*ft_path_token(t_cmd *cmd)
{
	struct stat	buf;
	char		*path;
	t_list		*path_list;

	if (stat(cmd->token[0], &buf) == 0)
	{
		path = ft_strdup(cmd->token[0]);
		if (!path)
			printf("dopisat exit\n");
		return (path);
	}
	path = ft_getset("PATH");
	if (!path)
		printf("dopisat exit\n");

	path_list = ft_crt_path_list(path, cmd);
	free(path);
	if (!path_list)
		printf("dopisat exit\n");

	return (ft_pathname(&path_list));
}

t_list	*ft_crt_path_list(char *path, t_cmd *cmd)
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
		if (!str)
			printf("dopisat exit\n");

		new = ft_lstnew(str);
		if (!new)
			printf("dopisat exit\n");

		ft_lstadd_back(&result, new);
	}
	return (result);
}

char	*ft_str_path(char **path, t_cmd *cmd)
{
	size_t	i;
	char	*result;
	char	*str;
	size_t	len;

	len = ft_strlen(cmd->token[0]);
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
	ft_memcpy((result + i + 1), cmd->token[0], len);
	result[i + len + 1] = 0;
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
			ft_lstclear(list, free);
			return (pathname);
		}
		path_list = path_list->next;
	}
	ft_lstclear(list, free);
	return (0);
}

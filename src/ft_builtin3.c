#include "minishell.h"

int	ft_pwd(char **cmd)
{
	char	*pwd;
	int		i;
	int		j;

	g_shell.status = 0;
	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
	return (1);
}

int ft_input_is_valid(char *s)
{
    int i;
    
    i = 0;
    while (s[i] && s[i] != '=')
    {
        if (i == 0)
        {
            if (s[i] != '_' && !ft_isalpha(s[i]))
            {
                g_shell.status = 1;
                return (0);
            }
        }
        else
        {
            if (s[i] != '_' && !ft_isalnum(s[i]))
            {
                g_shell.status = 1;
                return (0);
            }
        }
        i++;
    }
    return (1);
}

void    ft_clear_str(int j)
{
    int i;

    i = j;
    free(g_shell.set[j]);
    j++;
    while (g_shell.set[j])
    {
        g_shell.set[i] = g_shell.set[j];
        i++;
        j++;
    }
    g_shell.set[i] = 0;
}

int ft_unset(char **cmd)
{
    int i;
    int j;
    size_t len;

    i = 0;
    while (cmd[++i])
    {
        if (ft_input_is_valid(cmd[i]))
        {
            j = 0;
            while (g_shell.set[j])
            {
                len = ft_strlen(cmd[i]);
                if (!ft_strncmp(g_shell.set[j], cmd[i], len))
                {
                    if (g_shell.set[j][len] == '=')
                        ft_clear_str(j);
                }
                j++;
            }
        }

    }
	return (1);
}

char    **ft_sort_export(char **str)
{
    char    *sort;
    int     i;
    int     m;
    if (str == NULL)
        return (NULL);
    i = 0;
    m = 1;
    while (str[i] != NULL)
    {
        m = 1;
        while (str[i + m] != NULL)
        {
            if (ft_strncmp(str[i], str[i + m], ft_strlen(str[i])) > 0)
            {
                sort = str[i + m];
                str[i + m] = str[i];
                str[i] = sort;
            }
            m++;
        }
        i++;
    }
    return (str);
}

int ft_fn_selector(char **cmd)
{
	if (!ft_strncmp(cmd[0], "echo", 5))
		return (ft_echo(cmd));
	else if (!ft_strncmp(cmd[0], "cd", 3))
		return (ft_cd(cmd));
	else if (!ft_strncmp(cmd[0], "pwd", 4))
		return (ft_pwd(cmd));
	else if (!ft_strncmp(cmd[0], "export", 7))
		return (ft_export(cmd));
	else if (!ft_strncmp(cmd[0], "unset", 6))
		return (ft_unset(cmd));
	else if (!ft_strncmp(cmd[0], "env", 4))
		return (ft_env(cmd));
	else if (!ft_strncmp(cmd[0], "exit", 5))
		return (ft_exit(0, 0));
	return (0);
}
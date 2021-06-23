#include "minishell.h"

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
                //printf("<-Invalid input->\n");
                g_shell.status = 1;
                return (0);
            }
        }
        else
        {
            if (s[i] != '_' && !ft_isalnum(s[i]))
            {
                //printf("<-Invalid input->\n");
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
    printf("====================");
    printf("This is ur Val %s", g_shell.set[j]);
    printf("====================");
    free(g_shell.set[j]);
    j++;
    while (g_shell.set[j])
    {
        g_shell.set[i] = g_shell.set[j];
        i++;
        j++;
    }
    g_shell.set[i] = 0;
    //free(g_shell.set[i+1]);
}

int		ft_unset(char **cmd)
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

char        **ft_sort_export(char **str)
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

#include "minishell.h"

int ft_input_is_valid(char *s)
{
    int i;

    i = 0;
    while (s[i])
    {
        if (i == 0)
        {
            if (s[i] != '_' && !ft_isalpha(s[i]))
            {
                //printf("<-Invalid input->\n");
                return (0);
            }
        }
        else
        {
            if (s[i] != '_' || !ft_isalnum(s[i]) || s[i] != '=')
            {
                //printf("<-Invalid input->\n");
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
    while (g_shell.cmd_table->token[++i])
    {
        if (ft_input_is_valid(g_shell.cmd_table->token[i]))
        {
            j = 0;
            while (g_shell.set[j])
            {
                len = ft_strlen(g_shell.cmd_table->token[i]);
                if (!ft_strncmp(g_shell.set[j], g_shell.cmd_table->token[i], len))
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

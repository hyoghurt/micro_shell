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
                return (0);
        }
        else
        {
            if (s[i] != '_' && !ft_isalnum(s[i]))
                return (0);
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
    printf("This is ur Val %s", shell.set[j]);
    printf("====================");
    free(shell.set[j]);
    j++;
    while (shell.set[j])
    {
        shell.set[i] = shell.set[j];
        i++;
        j++;
    }
    shell.set[i] = 0;
    //free(shell.set[i+1]);
}

int		ft_unset(char **cmd)
{
    int i;
    int j;
    size_t len;

    i = 0;
    while (shell.cmd_table->token[++i])
    {
        if (ft_input_is_valid(shell.cmd_table->token[i]))
        {
            j = 0;
            while (shell.set[j])
            {
                len = ft_strlen(shell.cmd_table->token[i]);
                if (!ft_strncmp(shell.set[j], shell.cmd_table->token[i], len))
                {
                    if (shell.set[j][len] == '=')
                        ft_clear_str(j);
                }
                j++;
            }
        }

    }
	return (1);
}

#include "minishell.h"

void	ft_save_story(void)
{
	t_story	*tmp;
	char	*tmp_line;

	tmp = shell.story;
	tmp_line = ft_strdup(shell.line);
	free(tmp->str);
	tmp->str = ft_strdup(tmp_line);
	shell.line = tmp->str;
}

void	debag_check_story(void)
{
	t_story	*tmp;

	tmp = shell.story;

	while (tmp)
	{
		printf("story=%s\n", tmp->str);
		tmp = tmp->next;
	}
}

int		main(int argc, char **argv, char **envp)
{
	ft_init(envp);
	while (1)
	{
		ft_set_prompt();				//set prompt
		ft_read();						//read terminal	(create shell.line)
		ft_check_sintax_error();		//  !!!!!  write check ;;
		//debag_check_shell_line();		//debag shell.line
		write (1, "\n", 1);
		while (*shell.line)			//loop if have ';'
		{
			ft_parser();			//parser command line
			ft_executor();			//processing command
			if (*shell.line == ';')
				shell.line++;
			ft_cmdclear(&shell.cmd_table);
			//write func free shell.fd_in and out
		}
		debag_check_story();
	}
}

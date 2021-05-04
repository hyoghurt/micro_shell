#include "minishell.h"
#include <sys/wait.h>
#include <sys/stat.h>

void	check_token(void)
{
	char	**s;
	int		i;

	s = shell.cmd_table->token;
	i = 0;
	while (s[i])
	{
		printf("\e[1;38;5;10mtoken[%d]=\t[%s]\e[0m\n", i, s[i]);
		i++;
	}
	printf("\n");
}

void	check_status(void)
{
	printf("\e[1;38;5;10m\np shell.cmd_table=%p\e[0m\n", shell.cmd_table);
	printf("\e[1;38;5;10mstatus=[%d]\e[0m\n", shell.status);
	printf("\e[1;38;5;10mexit_executor\e[0m\n");
}

void	ft_executor(void)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;
	char	*str;

	check_token();	//debager
	str = ft_path_token();
	if (!str)
	{
		printf("minishell: command not found: %s\n", shell.cmd_table->token[0]);
		printf("NEED exit executor\n\n");
	}
	pid = fork();
	if (pid == 0)
	{
		if (execve(str, shell.cmd_table->token, shell.set) == -1)
			printf("minishell: command not found: %s\n", shell.cmd_table->token[0]);
		exit(0);	// нужна чтоб остановить процесс, копия у дочернего
	}
	else if (pid < 0)
		perror("fork");
	else
	{
		//do 
		//{
			wpid = waitpid(pid, &shell.status, WUNTRACED);
		//} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	ft_cmdclear(&shell.cmd_table);	//debager
	check_status();
}

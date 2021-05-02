#include "minishell.h"

void	ft_executor(char **envp)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;

	//fork();		-создается копия родительского процесса
	//execve();		-копия процесса подменяется новым (дочерним)
	//wait();		-ждем завершения дочернего процесса
	
	char	**s;
	int		i;

	s = shell.cmd_table->token;

	i = 0;
	while (s[i])
	{
		printf("s=[%s]\n", s[i]);
		i++;
	}
	/*
	pid = fork();
	if (execve(shell.cmd_table->token[0], shell.cmd_table->token, envp) == -1)
		perror("exec");
		*/
}

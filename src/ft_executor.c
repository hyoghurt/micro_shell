#include "minishell.h"
#include <sys/wait.h>

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

	status = 0;
	s = shell.cmd_table->token;
	i = 0;
	while (s[i])
	{
		printf("token[%d]=\t[%s]\n", i, s[i]);
		i++;
	}
	printf("\n");
	
	pid = fork();
	if (pid == 0)
	{
		if (execve(shell.cmd_table->token[0], shell.cmd_table->token, envp) == -1)
			printf("minishell: command not found: %s\n", shell.cmd_table->token[0]);
		exit(0);	// нужна чтоб остановить процесс копия у дочернего
	}
	else if (pid < 0)
		perror("fork");
	else
	{
		//do 
		//{
			wpid = waitpid(pid, &status, WUNTRACED);
		//} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	printf("\nstatus=[%d]\n", status);
	
	ft_cmdclear(&shell.cmd_table);
	shell.cmd_table = 0;
	printf("exit_executor\n");
	/*
	s = shell.cmd_table->token;

	i = 0;
	while (s[i])
	{
		printf("s=[%s]\n", s[i]);
		i++;
	}
	*/
	
}

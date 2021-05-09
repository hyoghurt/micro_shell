#include "minishell.h"

void	ft_read_character(char *buf);

void	ft_read(void)
{
	char	buf[10];						//buf for read

	while (1)
	{
		ft_memset(buf, 0, 10);				//zero buf
		if (read(0, buf, 10) < 0)
			ft_exit("read", "error");
		if (buf[0] == '\n')
			//if (ft_check_lexer(shell.line))		//check end string (no write)
			break ;
		ft_read_character(buf);		//check which character
	}
	shell.story->str = shell.line;
}

void	ft_read_character(char *buf)
{
	ft_init_shell_line();							//malloc for shell.line
	if (ft_strncmp(buf, shell.key.up, 3) == 0)			//key up
		ft_key_up();
	else if (ft_strncmp(buf, shell.key.down, 3) == 0)	//key down
		ft_key_down();
	else if (buf[0] == '\004')						//key C-D
		ft_exit(0, 0);								//write function
	else if (ft_strncmp(buf, shell.key.backsp, 2) == 0)	//key backspace
		ft_key_backsp();
	if ((buf[0] >= 32 && buf[0] <= 126) || (buf[0] >= 9 && buf[0] <= 13))
	{
		write (1, buf, ft_strlen(buf));
		ft_strlcat(shell.line, buf, ft_strlen(shell.line) + 2);
	}
}

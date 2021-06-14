#include "minishell.h"

void	ft_read_character(char *buf);

void	ft_read(void)
{
	char	buf[10];						//buf for read

	while (1)
	{
		ft_memset(buf, 0, 10);					//zero buf
		if (read(0, buf, 10) < 0)
			ft_exit("read", "error");
		if (buf[0] == '\n')						//check \n (end command)
			//if (ft_check_lexer(shell.line))		//check end string (check " and ')
			break ;
		ft_read_character(buf);					//check which character
	}
	shell.story->str = shell.line;				//add shell.line in story
	tcsetattr(0, TCSANOW, &shell.termios_p);
	write (1, "\n", 1);
}

void	ft_read_character(char *buf)
{
	ft_init_shell_line();										//realoc if it's necessary for shell.line
	if (ft_strncmp(buf, shell.key.up, 3) == 0)					//if key up
		ft_key_up();
	else if (ft_strncmp(buf, shell.key.down, 3) == 0)			//if key down
		ft_key_down();
	else if (buf[0] == '\004')									//if key C-D (!!!! need write function)
		ft_exit(0, 0);
	else if (buf[0] == '\177')			//if key backspace
		ft_key_backsp();
	if ((buf[0] >= 32 && buf[0] <= 126) || (buf[0] >= 9 && buf[0] <= 13))
	{
		write (1, buf, ft_strlen(buf));							//print char in terminal
		ft_strlcat(shell.line, buf, ft_strlen(shell.line) + 2);	//join character in shell.line
	}
}

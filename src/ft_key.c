#include "minishell.h"

char	*ft_key_up(char *line, char *up)
{
	//char	*down;
	//down	= tgetstr("do", 0);
	//char *kd = tgetstr("kd", 0);
	
	//if (strcmp(buf, up) == 0)		//key UP
	//	write (1, "UP", 2);
	//else if (strcmp(buf, kd) == 0)	//else if (buf[0] == '\n') //else if (strcmp(buf, "\033[B") == 0)
	//	write (1, "DO", 2);
}

char	*ft_key_backsp(char *line)
{
	char	*dc;

	dc = tgetstr("dc", 0);

	tputs("\b", 1, ft_putint);
	tputs(	dc, 1, ft_putint);
}

//	char	*right	= tgetstr("nd", 0);
//	char	*left	= tgetstr("le", 0);
//	char	*kl		= tgetstr("kl", 0);

//else if (strcmp(buf, "\033[D") == 0)	//key left else if (strcmp(buf, kl) == 0)	
//	write (1, buf, 2);
//else if (strcmp(buf, right) == 0)		//key right
//	write (1, "RG", 2);
//else if (buf[0] == '\004')				//key C-D
//	write (1, "C-D", 3);

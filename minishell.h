#ifndef MINISHELL_H
# define MINISHELL_H
# define BUF_SIZE 256

# include "libft.h"
# include <stdio.h>
# include <unistd.h>		//isatty
# include <string.h>		//strlen
# include <stdlib.h>		//getenv
# include <termcap.h>		//tgetent
# include <errno.h>			//errno
# include <ncurses.h>
# include <term.h>
# include <signal.h>

typedef struct		s_cmd
{
	char			**token;			//array command (example: cmd1 | cmd2 | cmd3)
	struct s_cmd	*next;
}					t_cmd;

typedef struct		s_shell
{
	struct termios	termios_p;

	char			**cache_bi;		//save storage command for up-arrow
	char			*line;			//string command
	t_cmd			*cmd_table;

	char			*out_file;
	char			*inp_file;
	char			*err_file;
	int				status;			//status exit
	char			**set;
}					t_shell;

t_shell	shell;

void	ft_free_bi(char **s);
int		ft_set_prompt(void);
int		ft_init_termtype(void);
int		ft_init_termios(void);
void	ft_init_struct(void);
char	*ft_read(void);
int		ft_putint(int c);
int		ft_print_error(void);
int		ft_exit(char *s);
void	ft_parser(void);
void	ft_executor(void);
void	ft_sigfunc(int sig);
char	*ft_key_up(char *line, char *up);
char	*ft_key_backsp(char *line); 
t_cmd	*ft_cmdnew(char **token);
void	ft_cmdadd_back(t_cmd **cmd, t_cmd *new);
void	ft_free_char(void *s);
char	**ft_crttkn_from_list(t_list *list);
void	ft_cmdclear(t_cmd **cmd);
void	ft_init(char **envp);
size_t	ft_array_len(char **envp);
char	**ft_cpy_array_bi(char **s1, char **s2);
char	*ft_getset(char *str);
char	*ft_path_token(void);

#endif

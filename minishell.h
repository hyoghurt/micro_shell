#ifndef MINISHELL_H
# define MINISHELL_H
# define BUF_SIZE 16

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
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>

//install libreadline-dev

typedef struct		s_story			//story
{
	char			*str;
	struct s_story	*back;
	struct s_story	*next;
}					t_story;

typedef struct		s_pid
{
	int				pid;
	struct s_pid	*next;
}					t_pid;

typedef struct		s_fd			//fd
{
	int				tmp_in;			//save stdin (0) need for restore stdin
	int				tmp_out;		//save stdout (1) need for restore stdout
	int				fd_in;
	int				fd_out;
	int				fd_in_file;
	int				fd_out_file;
}					t_fd;

typedef struct		s_cmd			//command
{
	char			**token;		//array command (example: cmd1 | cmd2 | cmd3)
	struct s_cmd	*next;
}					t_cmd;

typedef struct		s_key			//key
{
	char			*up;			//key up
	char			*down;			//key down
	char			*backsp;		//key backspace
	char			*dl;			//clear line
	char			*dc;			//kursor left
	char			*cd;			//delete screen end kursor
	char			*sc;			//save position kursor
	char			*rc;			//restore position kursor
	int				co;				//sum column
	int				li;				//sum row
}					t_key;

typedef struct		s_shell			//general
{
	struct termios	termios_p;		//standart terminal config

	struct s_story	*story;			//story
	struct s_story	*move_story;	//save pointer for move story
	int				fg_mv_story;	//flag for story move

	struct s_cmd	*cmd_table;		//table tokens (cmd_table->token | cmd_table->next->token ...)
	struct s_fd		std;			//fd (need for pipe)
	struct s_key	key;			//code key

	char			*line;			//string command
	char			**set;			//set variable (init: copy envp in set)

	char			*out_file;		//file stdout
	char			*in_file;		//file stdin

	char			*pathtkn;		//path_token for execve (execve(pathtkn, cmd_table->token, set)) (path command)

	int				status;			//status exit
	t_pid			*pid;
}					t_shell;

t_shell				shell;

t_story		*ft_story_new(char *str);
void		ft_story_add_back(t_story **story, t_story *new);
void		ft_story_add_front(t_story **story, t_story *new);
void		ft_story_clear(t_story **story);

t_cmd		*ft_cmdnew(char **token);
void		ft_cmdadd_back(t_cmd **cmd, t_cmd *new);
void		ft_cmdclear(t_cmd **cmd);

void	ft_init(char **envp);
int		ft_set_prompt(void);
void	ft_read(void);
void	ft_parser(void);
int		ft_executor(void);

void	ft_free_bi(char **s);
int		ft_putint(int c);
int		ft_print_error(void);
int		ft_exit(char *msg, char *s);

void	ft_sig_ctrl_c(int sig);
void	ft_key_up(void);
void	ft_key_down(void);
void	ft_key_backsp(void); 

char	**ft_crt_arr_bi_from_list(t_list *list);
size_t	ft_array_len(char **envp);
char	**ft_cpy_array_bi(char **s1, char **s2);
char	*ft_getset(char *str);
char	*ft_path_token(char **cmd);
void	ft_init_shell_line(void);

int		ft_lexer(void);

int		ft_save_stdin_stdout(void);
int		ft_fd_in(void);
int		ft_fd_out(void);
void	ft_fd_pipe(void);
int		ft_redirect_input(void);
int		ft_redirect_output(void);
void	ft_restore_fd(void);

void	debag_check_token(void);
void	debag_check_status(void);
void	debag_check_shell_line(void);
void	debag_check_story(void);

int		ft_fn_selector(void);
void	ft_builtin(void);



#endif

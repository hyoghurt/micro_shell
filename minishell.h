#ifndef MINISHELL_H
# define MINISHELL_H
# define BUF_SIZE 16
# define REDIR_MY "./src/redirect_tmp"

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
//story______________________________________
typedef struct		s_story			//story
{
	char			*str;
	struct s_story	*back;
	struct s_story	*next;
}					t_story;
//////////////////////////////////////////////
//pid_________________________________________
typedef struct		s_pid
{
	int				pid;
	struct s_pid	*next;
}					t_pid;
//////////////////////////////////////////////
//fd__________________________________________
typedef struct		s_fd			//fd
{
	int				tmp_in;
	int				tmp_out;
	int				fd_in;
	int				fd_out;
}					t_fd;
//////////////////////////////////////////////
//command (cmd1 | cmd2 | ...)_________________
typedef struct		s_cmd
{
	char			**token;
	int				fd_in;
	int				fd_out;
	char			*fd_in_file;
	char			*fd_out_file;
	struct s_cmd	*next;
}					t_cmd;
//////////////////////////////////////////////
//key_________________________________________
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
//////////////////////////////////////////////
//general_____________________________________
typedef struct		s_shell
{
	struct termios	termios_p;		//standart terminal config
	//story
	struct s_story	*story;			//story
	struct s_story	*move_story;	//save pointer for move story
	int				fg_mv_story;	//flag for story move
	//cmd
	struct s_cmd	*cmd_table;
	//fd
	struct s_fd		std;
	//key
	struct s_key	key;
	//pid
	struct s_pid	*pid;
	//line
	char			*line;
	//set
	char			**set;
	//pathtoken
	char			*pathtkn;
	//status
	int				status;
	//getenv(user) need for promt
	char			*user;
	//redirect tmp varible
	int				fd_in;
	int				fd_out;
	char			*fd_in_file;
	char			*fd_out_file;
}					t_shell;
//////////////////////////////////////////////
t_shell		shell;
//////////////////////////////////////////////
t_story		*ft_story_new(char *str);
void		ft_story_add_back(t_story **story, t_story *new);
void		ft_story_add_front(t_story **story, t_story *new);
void		ft_story_clear(t_story **story);
void		ft_story_del_front(t_story **story);


t_cmd		*ft_cmdnew(char **token);
void		ft_cmdadd_back(t_cmd **cmd, t_cmd *new);
void		ft_cmdclear(t_cmd **cmd);

void	ft_init(char **envp);
void	ft_start(void);
void	ft_read(void);
void	ft_parser(void);
int		ft_executor(void);

int		find_redirect_file(t_cmd *cmd);
void	ft_waitpid(void);
void	ft_killpid(void);

void	ft_free_bi(char **s);
int		ft_putint(int c);
int		ft_print_error(void);
void	ft_print_string(char *s1, char *s2, char *s3);
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
int		ft_check_lexer(void);

int		ft_save_stdin_stdout(void);
int		ft_fd_start(t_cmd *cmd);
int		ft_fd_end(t_cmd *cmd);
void	ft_fd_pipe(void);
int		ft_redirect_input(void);
int		ft_redirect_output(void);
void	ft_restore_fd(void);
int		ft_redirect(int one, int two);
int		ft_redirect_std(int one, int two);

void	debag_check_token(void);
void	debag_check_status(void);
void	debag_check_shell_line(void);
void	debag_check_story(void);

///t_pid
t_pid	*ft_pidnew(int n);
void	ft_addpid_back(t_pid **pid, t_pid *new);
void	ft_pidclear(t_pid **pid);


void	ft_string_ecran(char **string);
void	ft_string_status(char **string);
void	ft_string_env(char **string);
void	ft_string_word(char **string);
void	ft_string_quote(char **string, char c);

void	ft_strjoin_string(char **string, char *content);
void	ft_content(char **string, char *start);
int		ft_check_set(char check);
char	*ft_value_getset(void);

void	ft_parser_redirect(void);
void	ft_free_string(char **string);

void	ft_crt_lst(t_list **list);
char	*ft_crt_string(void);

///Built-in
int		ft_unset(void);
int		ft_fn_selector(void);
void	ft_builtin(void);

#endif

#ifndef MINISHELL_H
# define MINISHELL_H
# define BUF_SIZE 16
# define REDIR_MY "./src/redirect_tmp"

# include "libft.h"
# include <stdio.h>
# include <unistd.h>		//isatty
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

// # define PWD
// # define OLDPWD

//////////////////////////////////////////////
typedef struct s_story
{
	char			*str;
	struct s_story	*back;
	struct s_story	*next;
}					t_story;
//////////////////////////////////////////////
typedef struct s_pid
{
	int				pid;
	struct s_pid	*next;
}					t_pid;
//////////////////////////////////////////////
typedef struct s_fd
{
	int				tmp_in;
	int				tmp_out;
	int				fd_in;
	int				fd_out;
}					t_fd;
//////////////////////////////////////////////
typedef struct s_cmd
{
	char			**token;
	int				fd_in;
	int				fd_out;
	char			*fd_in_file;
	char			*fd_out_file;
	struct s_cmd	*next;
}					t_cmd;
//////////////////////////////////////////////
typedef struct s_key
{
	char			*up;
	char			*down;
	char			*backsp;
	/*clear line*/
	char			*dl;
	char			*dc;			//kursor left
	char			*cd;			//delete screen end kursor
	char			*sc;			//save position kursor
	char			*rc;			//restore position kursor
}					t_key;
//////////////////////////////////////////////
typedef struct		s_shell
{
	struct termios	termios_p;
	struct s_story	*story;
	struct s_story	*move_story;
	int				fg_mv_story;
	struct s_cmd	*cmd_table;
	struct s_fd		std;
	struct s_key	key;
	struct s_pid	*pid;
	char			*line;
	char			**set;
	char			*pathtkn;
	int				status;
	char			*user;
	int				fd_in;
	int				fd_out;
	char			*fd_in_file;
	char			*fd_out_file;
}					t_shell;
//////////////////////////////////////////////
t_shell		g_shell;
//////////////////////////////////////////////
t_story		*ft_story_new(char *str);
void		ft_story_add_back(t_story **story, t_story *new);
void		ft_story_add_front(t_story **story, t_story *new);
void		ft_story_del_front(t_story **story);
void		ft_story_clear(t_story **story);
//////////////////////////////////////////////
t_cmd		*ft_cmdnew(char **token);
void		ft_cmdadd_back(t_cmd **cmd, t_cmd *new);
void		ft_cmdclear(t_cmd **cmd);
//////////////////////////////////////////////
t_pid		*ft_pidnew(int n);
void		ft_addpid_back(t_pid **pid, t_pid *new);
void		ft_pidclear(t_pid **pid);
//////////////////////////////////////////////
void		ft_init(char **envp);
void		ft_start(void);
//////////////////////////////////////////////
void		ft_read(void);
void		ft_key_up(void);
void		ft_key_down(void);
void		ft_key_backsp(char *s); 
//////////////////////////////////////////////
int			ft_check_lexer(void);
int			ft_lexer(void);
//////////////////////////////////////////////
void		ft_parser(void);
char		*ft_crt_string(int f);
void		ft_string_ecran(char **string);
void		ft_string_status(char **string);
void		ft_string_env(char **string);
void		ft_string_word(char **string);
void		ft_string_quote_one(char **string);
void		ft_string_quote_two(char **string, int f);
void		ft_strjoin_string(char **string, char *content);
void		ft_content(char **string, char *start);
int			ft_check_start_set(char check);
char		*ft_getset(char *str);
char		*ft_value_getset(void);
//parser_add_2
void		ft_jump_space_and_pipe(void);
void		ft_jump_space(void);
int			ft_check_set(char c1, char c2);
int			ft_check_status(char c1, char c2);
//////////////////////////////////////////////




//////////////////////////////////////////////
//////////////////////////////////////////////
void		ft_parser_redirect(void);
void		ft_redir_content(char *string);
char		*ft_string_check_env(char *line);
//////////////////////////////////////////////
int			ft_executor(void);
int			ft_save_stdin_stdout(void);
void		ft_restore_fd(void);
int			ft_fd_start(t_cmd *cmd);
int			ft_fd_end(t_cmd *cmd);
int			ft_redirect(int one, int two);
void		ft_fd_pipe(void);
char		*ft_path_token(char **cmd);
void		ft_waitpid(void);
void		ft_killpid(void);
//////////////////////////////////////////////
void		ft_init_termios(void);
int			ft_set_prompt(void);
void		ft_free_bi(char **s);
int			ft_putint(int c);
int			ft_print_error(void);
void		ft_print_string(char *s1, char *s2, char *s3);
size_t		ft_array_len(char **envp);
char		**ft_cpy_array_bi(char **s1, char **s2);
char		**ft_crt_arr_bi_from_list(t_list *list);
void		ft_init_string(char **s);
void		ft_free_string(char **string);
void		ft_sig_ctrl_c(int sig);
//////////////////////////////////////////////
void		debag_check_token(void);
void		debag_check_status(void);
void		debag_check_shell_line(void);
void		debag_check_story(void);
//////////////////////////////////////////////
///Built-in
int			ft_fn_selector(char **cmd);
int			ft_exit(char *msg, char *s);
int			ft_unset(char **cmd);
int			ft_input_is_valid(char *s);
char        **ft_sort_export(char **str);
int			ft_var_is_present(char *s);
void		ft_swap_var_val(int i, char *s);


#endif

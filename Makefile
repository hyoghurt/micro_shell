NAME			= minishell
SRC				=	main.c	\
					ft_debag.c \
					ft_init.c \
					ft_key.c \
					ft_signal.c \
					ft_start.c \
					ft_read.c \
					ft_read_redirect.c \
					ft_read_redirect_2.c \
					ft_lexer.c \
					ft_lexer_2.c \
					ft_parser.c \
					ft_parser_add.c \
					ft_parser_add_2.c \
					ft_parser_redirect.c \
					ft_parser_str.c \
					ft_parser_str_quote.c \
					ft_executor.c \
					ft_fd.c \
					ft_fd_2.c \
					ft_path.c \
					ft_exec_add.c \
					ft_bl.c \
					ft_bl_echo.c \
					ft_bl_cd.c \
					ft_bl_env.c \
					ft_bl_export.c \
					ft_bl_export2.c \
					ft_bl_pwd.c \
					ft_bl_unset.c \
					ft_bl_exit.c \
					ft_add.c \
					ft_add_2.c \
					ft_struct_cmd.c \
					ft_struct_story.c \
					ft_struct_pid.c \
					ft_exit.c \

SRCDIR			= src
OBJDIR			= obj
OBJ				= $(addprefix $(OBJDIR)/,$(notdir $(SRC:.c=.o)))
CC				= gcc
CFLAGS			= -Wall -Wextra -Werror

$(NAME):		$(OBJ)
				make -C libft
				$(CC) $(OBJ) -ltermcap -lncurses -Llibft -lft -o $(NAME) 

$(OBJDIR):			
				mkdir -p $@

$(OBJDIR)/%.o:	$(SRCDIR)/%.c | $(OBJDIR)
				$(CC) $(CFLAGS) -I. -Ilibft -c -MD $< -o $@

include $(wildcard $(OBJDIR)/*.d)

all:			$(NAME)

clean:	
				rm -rf $(OBJDIR)
				make clean -C libft

fclean:			clean
				rm -rf $(NAME)
				make fclean -C libft

re:				fclean all
				make re -C libft

.PHONY:			all clean fclean re

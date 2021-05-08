NAME			= minishell
SRC				= main.c ft_init.c ft_parser.c ft_signal.c ft_exit.c ft_key.c ft_read.c ft_executor.c ft_add.c ft_path.c ft_lexer.c ft_debag.c ft_story.c
SRCDIR			= src
OBJDIR			= obj
OBJ				= $(addprefix $(OBJDIR)/,$(notdir $(SRC:.c=.o)))
CC				= gcc
CFLAGS			= -Wall -Wextra -Werror

$(NAME):		$(OBJ)
				make bonus -C libft
				$(CC) $(OBJ) -ltermcap -lncurses -Llibft -lft -o $(NAME) 

##-lncurses

$(OBJDIR):			
				mkdir -p $@

$(OBJDIR)/%.o:	$(SRCDIR)/%.c | $(OBJDIR)
				$(CC) -I. -Ilibft -c -MD $< -o $@

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

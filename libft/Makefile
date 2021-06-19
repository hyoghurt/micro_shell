# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pgurn <pgurn@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/15 16:59:33 by hyoghurt          #+#    #+#              #
#    Updated: 2021/06/20 00:51:48 by pgurn            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= libft.a
SRC				=	ft_memset.c \
					ft_putnstr.c \
					ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_strlen.c ft_strlcpy.c ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_atoi.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c
SRC_B			=	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

SRCDIR			= src
OBJDIR			= obj
OBJ				= $(addprefix $(OBJDIR)/,$(notdir $(SRC:.c=.o)))
OBJ_B			= $(addprefix $(OBJDIR)/,$(notdir $(SRC_B:.c=.o)))
CC				= gcc
CFLAGS			= -Wall -Wextra -Werror

$(NAME):		$(OBJ) | $(OBJ_B)
				ar rc $(NAME) $(OBJ) $(OBJ_B)
				ranlib $(NAME)

$(OBJDIR):			
				mkdir -p $@

$(OBJDIR)/%.o:	$(SRCDIR)/%.c | $(OBJDIR)
				$(CC) $(CFLAGS) -I. -Ilibft -c $< -o $@

all:			$(NAME)

bonus:			$(OBJ) | $(OBJ_B)
				ar rc $(NAME) $(OBJ_B) $(OBJ)
				ranlib $(NAME)

clean:	
				rm -rf $(OBJDIR)

fclean:			clean
				rm -rf $(NAME)

re:				fclean all

.PHONY:	all clean fclean re bonus

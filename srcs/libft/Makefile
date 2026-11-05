# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbutte <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/03 14:14:29 by jbutte            #+#    #+#              #
#    Updated: 2023/02/23 17:39:33 by jbutte           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = clang

FLAGS = -Wall -Wextra -Werror

SRCS =	ft_atoi.c	    		\
	   ft_bzero.c   			\
	   ft_calloc.c  			\
	   ft_isalnum.c 			\
	   ft_isalpha.c 			\
	   ft_isascii.c 			\
	   ft_isdigit.c 			\
	   ft_isprint.c 			\
	   ft_memchr.c  			\
	   ft_memcpy.c				\
	   ft_memcmp.c  			\
	   ft_memmove.c 			\
	   ft_memset.c  			\
	   ft_strchr.c  			\
	   ft_strdup.c  			\
	   ft_strlcat.c 			\
	   ft_strlcpy.c 			\
	   ft_strlen.c  			\
	   ft_strncmp.c 			\
	   ft_strnstr.c 			\
	   ft_strrchr.c 			\
	   ft_tolower.c 			\
	   ft_toupper.c 			\
	   ft_substr.c				\
	   ft_strjoin.c 			\
	   ft_strtrim.c 			\
	   ft_split.c   			\
	   ft_itoa.c				\
	   ft_strmapi.c 			\
	   ft_striteri.c			\
	   ft_putchar_fd.c 			\
	   ft_putstr_fd.c			\
	   ft_putendl_fd.c			\
	   ft_putnbr_fd.c			\
	   ft_lstnew.c				\
	   ft_lstadd_front.c		\
	   ft_lstsize.c				\
	   ft_lstlast.c				\
	   ft_lstadd_back.c			\
	   ft_lstdelone.c			\
	   ft_lstclear.c			\
	   ft_lstiter.c				\
	   ft_lstmap.c				\
	   ft_printf.c				\
	   ft_printf_utils.c		\
	   get_next_line.c			\
	   get_next_line_utils.c	\
	   comp_free_tab.c			\
	   comp_close_fds.c			\
	   comp_free_mtpstr.c		\
	   comp_error.c				\
	   comp_err_cmd_bash.c		\
	   comp_err_syntax_bash.c	\
	   comp_strdup_tab.c		\
	   comp_tablen.c			\
	   comp_tplstr_join.c		\
	   comp_rmvchar_str.c		\
	   comp_check_argc.c		\
	   comp_calloc2.c			\
	   comp_check_next_char.c	\

OBJS = $(SRCS:.c=.o)

%.o : %.c
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	ar -r $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
	
.PHONY: all clean fclean re bonus

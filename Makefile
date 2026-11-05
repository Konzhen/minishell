# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmennock <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/05 09:24:46 by jmennock          #+#    #+#              #
#    Updated: 2023/06/20 13:18:23 by jmennock         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#------------------------------------------------------------------------------#
#                                   EXECUTABLE                                 #
#------------------------------------------------------------------------------#

NAME		=	minishell

#------------------------------------------------------------------------------#
#                                   COMPILATION                                #
#------------------------------------------------------------------------------#

MAKEFLAGS	+=	--silent --no-print-directory

CC			=	clang

CFLAGS		=	-Wall -Werror -Wextra -g

DIRDUP		=	mkdir -p $(@D)

INCLUDE		= srcs/include

CPPFLAGS	= $(addprefix -I,$(INCLUDE))

#------------------------------------------------------------------------------#
#                                   FUNCTIONS                                  #
#------------------------------------------------------------------------------#

SRCS	=	srcs/minishell.c \

SRCS	+=	srcs/signal.c \

SRCS	+=	srcs/parsing/editor_view.c \
			srcs/parsing/is_between_quotes.c \
			srcs/parsing/strcspn_strspn.c \

SRCS	+=	srcs/parsing/create_tab/count_words_for_tab.c \
			srcs/parsing/create_tab/create_tab_segment.c \
			srcs/parsing/create_tab/create_tab_token.c \
			srcs/parsing/create_tab/create_token_for_tab_utils.c \
			srcs/parsing/create_tab/create_tab_char.c \
			srcs/parsing/create_tab/create_tab_to_exec.c \
			srcs/parsing/create_tab/create_token_for_tab.c \

SRCS	+=	srcs/parsing/checker/check_valid_line.c \
			srcs/parsing/checker/check_valid_line_utils.c \

SRCS	+=	srcs/parsing/cmd/get_cmds.c \
			srcs/parsing/cmd/get_cmds_utils.c \
			srcs/parsing/cmd/get_cmds_with_strtok.c \

SRCS	+=	srcs/parsing/expansion/e_utils.c \
			srcs/parsing/expansion/expand_all.c \
			srcs/parsing/expansion/expand_all_utils.c \
			srcs/parsing/expansion/expansion.c \
			srcs/parsing/expansion/token_expand_constructor.c \

SRCS	+=	srcs/free/free_management.c \

SRCS	+=	srcs/builtins/cd.c \
			srcs/builtins/echo.c \
			srcs/builtins/env.c \
			srcs/builtins/env_utils.c \
			srcs/builtins/exit.c \
			srcs/builtins/exit_next.c \
			srcs/builtins/export.c \
			srcs/builtins/export_utils.c \
			srcs/builtins/ft_strcmp.c \
			srcs/builtins/lst_to_array.c \
			srcs/builtins/modify_env.c \
			srcs/builtins/print_env.c \
			srcs/builtins/print_export.c \
			srcs/builtins/pwd.c \
			srcs/builtins/ttia_utils.c \
			srcs/builtins/turn_tok_into_array.c \
			srcs/builtins/unset.c \
			srcs/builtins/utils_env.c \

SRCS	+=	srcs/execution/efu_error.c \
			srcs/execution/execution_files_utils.c \
			srcs/execution/multi_closing.c \
			srcs/execution/pipeline_r_next.c \
			srcs/execution/pipeline_running.c \
			srcs/execution/reading.c \
			srcs/execution/running_management.c \

SRCS	+=	srcs/execution/redirection/exec_redirections.c \
			srcs/execution/redirection/open_for_redirection.c \
			srcs/execution/redirection/prepare_dup.c \
			srcs/execution/redirection/redir_heredoc.c \

SRCS	+=	srcs/utils/add_in_quotes.c \
			srcs/utils/count_segment.c \
			srcs/utils/get_redirection_type.c \
			srcs/utils/skip_spaces.c \
			srcs/utils/check_redirection_in_tab_char.c \
			srcs/utils/err_file_msg.c \
			srcs/utils/remove_quotes.c \

OBJ		= $(SRCS:%.c=$(BUILD_DIR)/%.o)

#------------------------------------------------------------------------------#
#                                     RULES                                    #
#------------------------------------------------------------------------------#

BUILD_DIR	=	.obj

all			:	$(NAME) 

$(NAME)		:	$(OBJ)
		@echo "\033[34mSTARTING ZOUK_PARTY\033[0m"
		make -C ./srcs/libft
		$(CC) $(CFLAGS) -L ./srcs/libft -I ./srcs/libft  $(OBJ) -l:libft.a -lreadline -o $(NAME)
		@echo "CREATED '\033[36m$(BUILD_DIR)\033[0m' location of *.o"
		@echo "CREATED EXECUTABLE '\033[33m$(NAME)\033[0m'"
		@echo "\033[32mZOUK_SHELL READY TO USE\033[0m"

bonus		:
			$(info no bonus)

$(BUILD_DIR)/%.o: %.c
		@$(DIRDUP)
		$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean		:
		@rm -rf $(OBJ)
		$(MAKE) -C ./srcs/libft clean
		@rm -rf $(BUILD_DIR)
		@echo "\033[31mENDING ZOUK_PARTY\033[0m"
		@echo "Suppression all files *.o"
		@echo "Suppression cached directory '\033[31m$(BUILD_DIR)\033[0m' for files *.o"

fclean		:	clean
		@rm -rf $(NAME)
		$(MAKE) -C ./srcs/libft fclean
		@echo "SUPPRESSION EXECUTABLE '\033[31m$(NAME)\033[0m'"

re			:	fclean all

.PHONY	: all clean fclean re

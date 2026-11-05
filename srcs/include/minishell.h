/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmennock <jimmy.mennock@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:23:43 by jmennock          #+#    #+#             */
/*   Updated: 2023/06/20 13:30:39 by jmennock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//--------------------------------------------------------------------------//
//	-							DEFINE										//
//--------------------------------------------------------------------------//

# ifndef ERR_QUOTES_NOT_CLOSED
#  define ERR_QUOTES_NOT_CLOSED "Quotes are not closed."
# endif

# ifndef ERR_SYNTAX
#  define ERR_SYNTAX "Syntax error detected."
# endif

//--------------------------------------------------------------------------//
//	- 							INCLUDES									//
//--------------------------------------------------------------------------//

# include "../libft/libft.h"
# include <errno.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

//--------------------------------------------------------------------------//
//	- 							VARIABLES									//
//--------------------------------------------------------------------------//

extern int	g_exit;

//--------------------------------------------------------------------------//
//	-							STRUCTURES									//
//--------------------------------------------------------------------------//

typedef enum e_enum_type {
	BUILT_IN,
	COMMAND,
	ARG,
	REDIR,
	TFILE,
	END,
	ERROR,
	EMPTY
}	t_enum_type;

typedef enum e_redirection_type {
	HEREDOC,
	IN,
	OUT,
	APPEND_OUT,
	NOT_REDIR
}	t_redirection;

typedef struct s_env {
	bool			print_export;
	bool			print_env;
	char			*variable;
	char			*value;
	int				index;
	struct s_env	*next;
}	t_env;

typedef struct s_exc {
	pid_t	*pid_array;
	int		read;
	int		write;
	int		pipefd[2];
	int		index;
	int		len;
}	t_exc;

typedef struct s_cmd {
	char	**tab_cmd;
	char	*path_cmd;
}	t_cmd;

typedef struct s_file {
	t_redirection	redir_type;
	char			*name;
	int				fd;
	int				hdfd[2];
}	t_file;

typedef struct s_token {
	t_enum_type		type;
	t_cmd			*cmd;
	t_file			*file;
	char			*expanded;
	bool			double_quotes;
	int				tool_len;
	char			*tool_str;
	char			**word;
}	t_token;

typedef struct s_tta_tool {
	size_t	len;
	size_t	i;
	size_t	j;
}	t_tta_tool;

//--------------------------------------------------------------------------//
//	-							FUNCTIONS									//
//--------------------------------------------------------------------------//

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~./SRCS/

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~./SRCS/EXECUTION/

//reading.c
void			ft_read_input(char *str, char **env);

//signal.c
int				for_rl_event_hook(void);
void			set_signal(void);
void			set_hd_signal(void);
void			ctrl_c(int signal);
void			ctrl_d(int signal);

//multi_managment.c
void			multi_closing(int a, int b, int c, int d);

//running_managment.c
bool			running_managment(t_token **tab, t_env **p_envlst);

//execution_files_utils.c
bool			dispatching(t_token **segment, int index, \
					t_env **p_envlst, pid_t pid);
bool			exec_builtin(t_token **segment, int index_up, \
					t_env **p_envlst, pid_t pid);
void			exec_cmd(t_token *token, char **env);

//efu_error.c
void			error_gestion(t_token **token, char **env, \
					int index_up, int index_deep);
void			error_if_redir_fail(t_token **segment, t_env **p_envlst, \
					char **env_toexec);

//pipeline_running.c
bool			pipeline_running(t_token **array, t_env **p_envlst);

//pipeline_r_next.c
void			pipeline_r_next(t_exc *tool);
void			destroy_error(t_token **array, t_env **p_envlst);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~./SRCS/PARSING/

//editor_view.c
bool			is_not_valid_syntax(char *str);
bool			is_space(char c);

//quotes_checking.c
int				is_quote_closed(char *str);
char			*ft_strtok(char *src_str, char *delim);

//is_between_quotes.c
bool			is_between_quotes(bool *state, char c);

//strcspn_strspn.c
size_t			ft_strcspn(char *s1, char *s2);
size_t			ft_strspn(char *s1, char *s2);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~./SRCS/PARSING/CHECKER/

//check_valid_line.c
bool			check_valid_line(char *line);

//check_valid_line_utils.c
void			skip_quotes(char *line, int *i);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~./SRCS/PARSING/CREATE_TAB/

//count_words_for_tab.c
int				count_words_for_tab(char *segment);

//create_tab_char.c
char			**create_tab_char(char *segment);

//create_tab_segment.c
char			**create_tab_segment(char *line, int count);

//create_tab_token.c
t_token			*create_tab_token(char **tab_char, t_env **p_envlst);

//create_tab_minishell.c
t_token			**create_tab_to_exec(char *line, t_env **p_envlst);

//create_token_for_tab.c
bool			create_file_token(t_token *token, char *tab_word, \
					t_token redir, t_env **p_envlst);
bool			create_redir_token(t_token *token, char *tab_word);
bool			create_exec_token(t_token *token, char *tab_word, int *index);

//create_token_for_tab_utils.c
bool			calloc_token_if_cmd(t_token *token, char *tab_word);
t_enum_type		is_builtin(char *token_word);
bool			fill_token_file(t_token *token, char *tab_word, t_token redir, \
					t_env **p_envlst);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~./SRCS/PARSING/CMD/

//get_cmd_utils.c
int				calculate_args(t_token *segment);
char			*get_path(char **env);

//get_cmds.c
bool			get_cmds(t_token *segment, char **envp);

//get_cmds_with_strtok.c
bool			is_executable_file(char const *path);
bool			is_directory(char const *path);
char			*get_path_cmd(char **path, char const *word);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~./SRCS/PARSING/EXPANSION/

//expand_all.c
void			do_expansion_all(t_token **token, t_env **p_envlst);

//expand_all_utils.c
t_enum_type		is_builtin_expanded(t_token *token);
bool			fill_token_word(t_token *token, char **tab_char);

//expansion.c
void			expansion(t_env **p_envlst, t_token *token);
char			*expand_global(char **pmove, char **p_expand, t_token *token);

//e_utils.c
char			*choose_expansion(t_env **penvlst, char **pmove, char **p_exp, \
					t_token *token);

//token_expansion_constructor.c
void			multiple_freeing(char *s1, char *s2, char *s3, char *s4);
char			*is_expand(t_env **p_envlst, char **p_to_move, \
					char **p_expand, t_token *token);
void			handle_expanded_case(char **pmove, \
					char **p_expd, t_token *token);

//split_quotes.c
char			**ft_split_quotes(char *s, char c);

//sq_tool.c
bool			is_not_quoted(char *str, int index);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~./SRCS/PARSING/REDIR/

//redir_heredoc.c
bool			redir_heredoc(t_file *file);

//open_for_redirections.c
void			open_files(t_token **tab, bool heredoc);
void			open_for_redirection(t_token **tab);

//prepare_dup.c
bool			prepare_dup(t_token *segment, int *fd_in, int *fd_out);

//exec_redirections.c
bool			exec_multi_redirections(t_token *segment, t_exc *tool);
bool			exec_redirections(t_token *segment);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~./SRCS/BUILTIN/

//exit.c
bool			ft_exit(char **status, t_env **p_envlt);

//exit_next.c
bool			msg_exit_error(char *status, int *value);

//utils_env.c
void			node_destroy(t_env *node);
void			lst_destroy(t_env *lst);

//lst_to_array.c
bool			e_builtin(char **towork, char *str, \
					t_env **p_envlst, pid_t pid);
char			**lst_to_array(t_env **p_envlst);

//env.c
t_env			*ft_env(char **envp, pid_t pid);
t_env			*init_env(char *variable, char *value, int index);
t_env			*ft_node_creat(char *str, pid_t pid);

//env_utils.c
t_env			*envlstlast(t_env *lst);
int				find_equal(char *str);
void			add_back_env(t_env **lst, t_env *node);

//print_env.c
void			ft_print_env(t_env **envlst);

//pwd.c
void			ft_pwd(void);

//cd.c
void			ft_cd(t_env **lst, char **str, pid_t pid);

//ft_strcmp.c
int				ft_strcmp(char *s1, char *s2);

//echo.c
void			echo(char **array);

//export.c
void			ft_export(t_env **p_envlst, char **array, pid_t pid);
char			*is_valid_var_name(char *str, int pos, pid_t pid);
bool			is_right_first_cara(char *str);

//print_export.c
void			print_export(t_env **p_envlst);

//export_utils.c
char			*get_value(t_env *p_variable);
t_env			*get_variable(t_env **p_envlst, char *variable);
bool			var_is_in_env(t_env **p_envlst, char *variable);
char			*fine_variable(char *str);

//unset.c
void			unset(t_env **p_envlst, char **array);

//modify_env.c
void			modify_value_in_env(t_env **p_envlst, char *str);

//turn_tok_into_array.c
char			**turn_tok_into_array(t_token **segment, int index_up);

//ttia_utils.c
void			setup_ttia(t_tta_tool *tool, t_token **segment, int index_up);
bool			clean_fill_array(char **array, t_tta_tool *tool, \
					t_token **segment, int index_up);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~./SRCS/FREE/

//free_management.c
void			tok_free(t_token ***token);
void			clean_fd(void);
void			close_and_free_all(bool to_close, t_token **tab);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~./SRCS/UTILS/

bool			check_redirection_in_tab_char(const char *tab_word);
char			*remove_quotes(const char *token_word);
bool			check_in_quotes(char *line);
int				add_in_quotes(char *segment, int *i);
int				skip_spaces(char *line, int *i);
int				count_segment(char *line);
t_redirection	get_redirection_type(char *token_word);
void			err_file_msg(char *name, bool is_valid_name);

#endif

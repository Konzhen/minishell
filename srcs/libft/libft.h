/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbutte <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:14:21 by jbutte            #+#    #+#             */
/*   Updated: 2023/01/30 17:28:46 by jbutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <stdarg.h>
# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include "get_next_line.h"

//-------------------------------------------------------//

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

//-------------------------------------------------------//

//	libft_base
int		ft_atoi(const char	*s);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_tolower(int c);
int		ft_toupper(int c);
int		ft_cntwrd(char const *s, char c);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strrchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

//	t_list
int		ft_lstsize(t_list *lst);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

//-------------------------------------------------------//
//	complements

int		free_tab(void **tab, size_t size);
int		close_fds(int nb_fd, ...);
int		free_mtpstr(int nb_fd, ...);
char	check_next_char(char *src, char *str);
char	**strdup_tab(char **tab);
char	*tplstr_join(const char *s1, const char *s2, const char *s3);
char	*rmvchar_str(const char *src, char c);
void	err_std(char *msg);
void	err_cmd_bash(char *cmd);
void	err_syntax_bash(char *cmd);
int		check_argc(int argc, unsigned int min, unsigned int max);
void	*calloc2(size_t nmemb, size_t size, char *msg);
size_t	tablen(void **tab);

//-------------------------------------------------------//
//	ft_printf
int		ft_printf(const char *format, ...);
int		type_to_print(va_list lst, char format);
int		check_format(char c);
void	ft_putchar_printf(char c, int *value);
void	ft_putstr_printf(char *s, int *value);
void	ft_putnbr_printf(long int n, char *base, int *value);
void	ft_putpointer_printf(unsigned long n, char *base,
			int *boolp, int *value);

#endif

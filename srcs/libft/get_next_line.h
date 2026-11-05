/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbutte <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 22:07:32 by jbutte            #+#    #+#             */
/*   Updated: 2023/01/29 22:07:35 by jbutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include "libft.h"
# include <fcntl.h>

size_t	ft_strlen_gnl(const char *str);
void	*ft_calloc_gnl(size_t nmemb, size_t size);
char	*ft_strjoin_gnl(char *s1, char *s2);
char	*ft_strchr_gnl(const char *s, int c);
char	*get_next_str(int fd);
char	*get_next_line(int fd);
char	*prepare_next_line(char *buf);
void	prepare_buf(char *buf);
int		read_if_empty(int fd, char *buf);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbutte <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 22:06:40 by jbutte            #+#    #+#             */
/*   Updated: 2023/01/29 22:07:07 by jbutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

int	read_if_empty(int fd, char *buf)
{
	int		read_value;

	read_value = 1;
	if (!buf)
		return (0);
	if (!*buf)
		read_value = read(fd, buf, BUFFER_SIZE);
	return (read_value);
}

void	prepare_buf(char *buf)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (ft_strchr_gnl(buf, '\n'))
	{
		while (buf[i] != '\n')
			i++;
		if (buf[i] == '\n')
			i++;
		while (buf[i] != '\0')
		{
			buf[j] = buf[i];
			j++;
			i++;
		}
		buf[j] = '\0';
	}
	while (j < BUFFER_SIZE)
	{
		buf[j] = '\0';
		j++;
	}
}

char	*prepare_next_line(char *buf)
{
	char	*next_str;
	int		size;
	int		i;

	size = 0;
	i = 0;
	while (buf[size] != '\n' && buf[size] != '\0')
		size++;
	if (buf[size] == '\n')
		size++;
	next_str = ft_calloc_gnl(size + 1, sizeof(char));
	while (i < size)
	{
		next_str[i] = buf[i];
		i++;
	}
	prepare_buf(buf);
	return (next_str);
}

char	*get_next_str(int fd)
{
	static char	buf[1024][BUFFER_SIZE + 1];
	char		*next_line;
	int			read_value;

	buf[fd][BUFFER_SIZE] = '\0';
	read_value = read_if_empty(fd, buf[fd]);
	next_line = NULL;
	if (read_value <= 0)
		return (NULL);
	if (ft_strchr_gnl(buf[fd], '\n'))
	{
		next_line = prepare_next_line(buf[fd]);
		return (next_line);
	}
	while (!ft_strchr_gnl(buf[fd], '\n'))
	{
		next_line = ft_strjoin_gnl(next_line, prepare_next_line(buf[fd]));
		read_value = read_if_empty(fd, buf[fd]);
		if (!read_value)
			return (next_line);
	}
	next_line = ft_strjoin_gnl(next_line, prepare_next_line(buf[fd]));
	return (next_line);
}

char	*get_next_line(int fd)
{
	char	*line;

	if (fd < 0 || BUFFER_SIZE == 0)
		return (NULL);
	line = get_next_str(fd);
	return (line);
}

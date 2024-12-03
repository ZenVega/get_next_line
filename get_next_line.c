/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:06:14 by uschmidt          #+#    #+#             */
/*   Updated: 2024/12/03 14:44:36 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*dest;

	i = 0;
	dest = (char *)s;
	while (i < n)
		dest[i++] = 0;
}

int	get_newline_chr(char *str, int buff_len)
{
	int	i;

	i = 0;
	while (i < buff_len && str[i] != '\n')
		i++;
	return (i);
}

char	*extend_line(char *line, int size)
{
	char	*linebuffer;
	int		line_length;

	line_length = 0;
	if (line)
		line_length = ft_strlen(line);
	linebuffer = (char *)malloc(sizeof(char) * (line_length + size + 1));
	ft_bzero(linebuffer, (line_length + size + 1));
	if (!linebuffer)
		return (NULL);
	if (line)
	{
		ft_memmove(linebuffer, line, line_length);
		free(line);
	}
	return (linebuffer);
}

char	*get_line(int fd, char *buffer)
{
	int			i;
	int			buff_len;
	char		*line;
	ssize_t		read_bytes;

	buff_len = ft_strlen(buffer);
	i = get_newline_chr(buffer, buff_len);
	line = NULL;
	while (i == buff_len)
	{
		line = extend_line(line, i);
		ft_memmove(line + ft_strlen(line), buffer, i);
		line[i + ft_strlen(line)] = '\0';
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes <= 0)
			break ;
		buff_len = ft_strlen(buffer);
		i = get_newline_chr(buffer, buff_len);
	}
	line = extend_line(line, i);
	ft_memmove(line + ft_strlen(line), buffer, i + 1);
	line[i + ft_strlen(line)] = '\0';
	ft_memmove(buffer, buffer + i + 1, BUFFER_SIZE - i);
	ft_bzero(buffer + (BUFFER_SIZE - i - 1), i + 1);
	return (line);
}

char	*get_next_line(int fd)
{
	ssize_t		read_bytes;
	static char	*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer)
	{
		buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE);
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes <= 0)
			return (NULL);
	}
	if (buffer[0] == '\0')
		return (NULL);
	return (get_line(fd, buffer));
}

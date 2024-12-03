/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:06:14 by uschmidt          #+#    #+#             */
/*   Updated: 2024/12/03 10:48:40 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int	get_newline_chr(char *str)
{
	int	i;

	i = 0;
	while (i < BUFFER_SIZE && str[i] != '\n')
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
	linebuffer = (char *)malloc(sizeof(char) * (line_length + size));
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
	char		*line;
	ssize_t		read_bytes;

	write(1, "DEBUGGER_1\n", 11);
	i = get_newline_chr(buffer);
	line = NULL;
	while (i == BUFFER_SIZE)
	{
		line = extend_line(line, i);
		line = ft_memmove(line + ft_strlen(line), buffer, i);
		line[i + ft_strlen(line) + 1] = '\0';
		read_bytes = read(fd, buffer, i);
		i = get_newline_chr(buffer);
	}
	line = extend_line(line, i);
	write(1, "DEBUGGER_2\n", 11);
	line = ft_memmove(line + ft_strlen(line), buffer, i);
	write(1, "DEBUGGER_3\n", 11);
	line[i + ft_strlen(line) + 1] = '\0';
	ft_memmove(buffer, buffer + BUFFER_SIZE - i, i);
	write(1, "DEBUGGER_4\n", 11);
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
	return (get_line(fd, buffer));
}

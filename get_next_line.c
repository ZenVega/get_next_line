/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:16:07 by uschmidt          #+#    #+#             */
/*   Updated: 2024/11/29 17:39:06 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int	get_next_lb(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n' && i < BUFFER_SIZE)
		i++;
	return (i + (str[i] == '\n'));
}

char	*get_line(int fd, char *buffer)
{
	int			i;
	int			multi;
	char		*line;
	char		*linestart;
	char		*linebuffer;
	ssize_t		read_bytes;

	multi = 1;
	i = get_next_lb(buffer);
	line = (char *)malloc(sizeof(char) * i + 1);
	linestart = line;
	if (!line)
		return (NULL);
	ft_memmove(line, buffer, i);
	i = get_next_lb(line);
	while (i > BUFFER_SIZE)
	{
		read_bytes = read(fd, buffer + (BUFFER_SIZE - i), i);
		i = get_next_lb(buffer);
		linebuffer = ft_strdup(line);
		free(line);
		line = (char *)malloc(sizeof(char) * BUFFER_SIZE * multi + i + 1);
		line = ft_strdup(linebuffer);
		free(linebuffer);
		ft_memmove(line, buffer, i);
	}
	line[i] = '\0';
	ft_memmove(buffer, buffer + i, (BUFFER_SIZE - i));
	read_bytes = read(fd, buffer + (BUFFER_SIZE - i), i);
	if (read_bytes < i)
		buffer[BUFFER_SIZE - i + read_bytes] = '\0';
	return (linestart);
}

char	*get_next_line(int fd)
{
	ssize_t		read_bytes;
	static char	*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer)
	{
		buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes <= 0)
			return (NULL);
		buffer[read_bytes] = '\0';
	}
	return (get_line(fd, buffer));
}

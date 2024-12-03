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
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

char	*extend_line(char *line, int size)
{
	char	*linebuffer;

	linebuffer = (char *)malloc(sizeof(char) * size);
	ft_memmove(linebuffer, line, size);
	free(line);
	return (linebuffer);
}

char	*get_line(int fd, char *buffer)
{
	int			i;
	char		*line;
	ssize_t		read_bytes;

	printf("BUFFER: %s //\n", buffer);
	i = get_next_lb(buffer);
	line = (char *)malloc(sizeof(char) * i + 1);
	ft_memmove(line, buffer, i);
	if (!line)
		return (NULL);
	while (i == BUFFER_SIZE)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE - 1);
		buffer[BUFFER_SIZE] = '\0';
		i = get_next_lb(buffer);
		line = extend_line(line, (ft_strlen(line) + i + 1));
		ft_memmove(&line[(ft_strlen(line) + 1)], buffer, i);
	}
	ft_memmove(buffer, buffer + i, (BUFFER_SIZE - i));
	printf("BUFFER_mid: %s //\n", buffer);
	//THIS CALL FOR READ AINT WORKING!!!
	read_bytes = read(fd, buffer + (BUFFER_SIZE - i - 1), i);
	printf("READ: %zd //\n", read_bytes);
	buffer[BUFFER_SIZE] = '\0';
	printf("BUFFER_after: %s //\n", buffer);
	if (read_bytes < i)
		buffer[BUFFER_SIZE - i + read_bytes] = '\0';
	line[i + 1] = '\0';
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
		read_bytes = read(fd, buffer, BUFFER_SIZE - 1);
		if (read_bytes <= 0)
			return (NULL);
		buffer[read_bytes - 1] = '\0';
	}
	return (get_line(fd, buffer));
}

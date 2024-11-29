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
	while (str[i] != '\n' && i < BUFFER_SIZE)
		i++;
	return (i + 1);
}

char	*get_next_line(int fd)
{
	ssize_t		read_bytes;
	static char	*buffer;
	char		*line;
	char		*linestart;
	int			i;

	line = (char *)malloc(sizeof(char) * 20 * BUFFER_SIZE);
	linestart = line;
	if (!buffer)
	{
		buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE);
		read_bytes = read(fd, buffer, BUFFER_SIZE);
	}
	else
	{
		i = get_next_lb(buffer);
		while (i > BUFFER_SIZE)
		{
			ft_memmove(line, buffer, BUFFER_SIZE);
			//write(1, "DEBUGGER_1\n", 11);
			printf("LINE %s --\n", line);
			line += BUFFER_SIZE;
			read_bytes = read(fd, buffer, BUFFER_SIZE);
			i = get_next_lb(buffer);
		}
		ft_memmove(buffer, buffer + i, (BUFFER_SIZE - i));
		read_bytes = read(fd, buffer + (BUFFER_SIZE - i), i);
	}
	i = get_next_lb(buffer);
	ft_memmove(line, buffer, i);
	line[i + 1] = '\0';
	return (linestart);
}

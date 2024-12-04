/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:41:37 by uschmidt          #+#    #+#             */
/*   Updated: 2024/12/04 15:24:39 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

void	*ft_calloc(size_t size)
{
	unsigned char	*ptr;
	unsigned int	i;

	if (size <= 0)
		return (NULL);
	ptr = (unsigned char *)malloc(sizeof(char) * size);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < size)
		ptr[i++] = 0;
	return (ptr);
}

int	get_newline_chr(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] && str[i] == '\n')
		return (i);
	return (0);
}

char	*merge_strs(char *first, char *second)
{
	int		first_len;
	int		second_len;
	char	*result;

	first_len = ft_strlen(first);
	second_len = ft_strlen(second);
	result = ft_calloc(first_len + second_len + 1);
	if (result)
	{
		ft_memmove(result, first, first_len);
		ft_memmove(result + first_len, second, second_len + 1);
	}
	free(first);
	return (result);
}

char	*read_to_nl(int fd, char *buffer)
{
	ssize_t	read_bytes;
	char	*read_str;

	if (get_newline_chr(buffer))
		return (buffer);
	read_str = ft_calloc(BUFFER_SIZE + 1);
	read_bytes = 1;
	while (read_bytes > 0)
	{
		read_bytes = read(fd, read_str, BUFFER_SIZE);
		if (read_bytes < 0)
		{
			free(buffer);
			buffer = NULL;
			return (NULL);
		}
		read_str[read_bytes] = 0;
		buffer = merge_strs(buffer, read_str);
		if (!buffer)
			return (NULL);
		if (get_newline_chr(buffer))
			break ;
	}
	free(read_str);
	return (buffer);
}

char	*extract_line(char *buffer)
{
	int		nl;
	char	*line;
	int		to_clear;

	nl = get_newline_chr(buffer);
	line = ft_calloc(nl + 1);
	if (!line)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	ft_memmove(line, buffer, nl);
	to_clear = ft_strlen(buffer) - nl;
	ft_memmove(buffer, buffer + nl + 1, to_clear);
	buffer[to_clear] = 0;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer)
	{
		buffer = ft_calloc(1);
		if (!buffer)
			return (NULL);
		buffer[0] = 0;
	}
	buffer = read_to_nl(fd, buffer);
	if (buffer && buffer[0] != 0)
		return (extract_line(buffer));
	free(buffer);
	buffer = NULL;
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:14:40 by uschmidt          #+#    #+#             */
/*   Updated: 2024/12/05 15:20:58 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>

int	get_newline_chr(char *str)
{
	long long	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*merge_strs(char *first, char *second)
{
	int		first_len;
	int		second_len;
	char	*result;

	first_len = 0;
	if (first)
		first_len = ft_strlen(first);
	second_len = ft_strlen(second);
	result = ft_calloc(first_len + second_len + 1);
	if (!result)
		return (NULL);
	if (first)
	{
		ft_memmove(result, first, first_len);
		free(first);
	}
	ft_memmove(result + first_len, second, second_len + 1);
	return (result);
}

char	*read_to_nl(int fd, char **buffer_arr)
{
	ssize_t	read_bytes;
	char	*read_str;

	read_str = ft_calloc(BUFFER_SIZE + 1);
	if (!read_str)
		return (NULL);
	read_bytes = 1;
	while (read_bytes > 0)
	{
		read_bytes = read(fd, read_str, BUFFER_SIZE);
		if (read_bytes == 0 && buffer_arr[fd][0] == '\0')
		{
			free(buffer_arr[fd]);
			buffer_arr[fd] = NULL;
			break ;
		}
		if (read_bytes < 0)
			return (free_all(buffer_arr[fd], &read_str));
		read_str[read_bytes] = 0;
		buffer_arr[fd] = merge_strs(buffer_arr[fd], read_str);
		if (!buffer_arr[fd])
			return (NULL);
		if (get_newline_chr(buffer_arr[fd]) != -1)
			break ;
	}
	free(read_str);
	return (buffer_arr[fd]);
}

char	*extract_line(char *buffer)
{
	int		nl;
	char	*line;
	int		to_clear;

	nl = get_newline_chr(buffer) + 1;
	if (!nl)
		nl = ft_strlen(buffer);
	line = ft_calloc(nl + 1);
	if (!line)
	{
		buffer = NULL;
		return (buffer);
	}
	ft_memmove(line, buffer, nl);
	to_clear = ft_strlen(buffer) - nl;
	ft_memmove(buffer, buffer + nl, to_clear);
	buffer[to_clear] = 0;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	**buffer_arr;
	int			i;

	printf("FD: %d\n", fd);
	if ((fd < 0 && fd > FD_MAX) || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (!buffer_arr)
	{
		i = 0;
		buffer_arr = (char **)malloc(sizeof(char *) * FD_MAX);
		if (!buffer_arr)
			return (NULL);
		while (i < FD_MAX)
			buffer_arr[i++] = NULL;
	}
	if (!buffer_arr[fd])
	{
		buffer_arr[fd] = ft_calloc(1);
		if (!buffer_arr[fd])
			return (NULL);
		buffer_arr[fd][0] = 0;
	}
	buffer_arr[fd] = read_to_nl(fd, buffer_arr);
	if (!buffer_arr[fd])
		return (free_buffers(buffer_arr));
	if (buffer_arr[fd][0] != 0)
		return (extract_line(buffer_arr[fd]));
	return (free_buffers(buffer_arr));
}

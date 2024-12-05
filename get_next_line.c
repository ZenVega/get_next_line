/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:41:37 by uschmidt          #+#    #+#             */
/*   Updated: 2024/12/04 16:32:46 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

char	*read_to_nl(int fd, char *buffer)
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
		if (read_bytes == 0)
			break ;
		if (read_bytes < 0)
			return (free_all(&buffer, &read_str));
		read_str[read_bytes] = 0;
		buffer = merge_strs(buffer, read_str);
		if (!buffer)
			return (NULL);
		if (get_newline_chr(buffer) != -1)
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
	if (!buffer)
		return (NULL);
	if (buffer[0] != 0)
		return (extract_line(buffer));
	return (free_all(&buffer, NULL));
}

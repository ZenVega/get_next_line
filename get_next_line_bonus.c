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
	result = ft_calloc(first_len + second_len + 1, 1);
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

	read_str = ft_calloc(BUFFER_SIZE + 1, 1);
	if (!read_str)
		return (NULL);
	read_bytes = 1;
	while (read_bytes > 0)
	{
		read_bytes = read(fd, read_str, BUFFER_SIZE);
		if (read_bytes == 0)
			break ;
		if (read_bytes < 0)
			return (free_all(buffer_arr[fd], read_str));
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

char	*extract_line(char **buffer_arr, int fd)
{
	int		nl;
	char	*line;
	int		to_clear;
	int		str_len;

	nl = get_newline_chr(buffer_arr[fd]) + 1;
	if (!nl)
		nl = ft_strlen(buffer_arr[fd]);
	line = ft_calloc(nl + 1, 1);
	if (!line)
	{
		buffer_arr[fd] = NULL;
		return (buffer_arr[fd]);
	}
	ft_memmove(line, buffer_arr[fd], nl);
	to_clear = ft_strlen(buffer_arr[fd]) - nl;
	ft_memmove(buffer_arr[fd], buffer_arr[fd] + nl, to_clear);
	str_len = ft_strlen(buffer_arr[fd]);
	while (to_clear <= str_len)
		buffer_arr[fd][to_clear++] = 0;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer_arr[FD_MAX];
	char		*line;

	if (fd < 0 || fd >= FD_MAX || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (buffer_arr[fd] == 0)
		buffer_arr[fd] = ft_calloc(1, 1);
	if (!buffer_arr[fd])
		return (NULL);
	buffer_arr[fd] = read_to_nl(fd, buffer_arr);
	if (buffer_arr[fd] && buffer_arr[fd][0] == '\0')
	{
		free(buffer_arr[fd]);
		buffer_arr[fd] = NULL;
		return (NULL);
	}
	line = extract_line(buffer_arr, fd);
	return (line);
}

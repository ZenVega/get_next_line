/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:16:07 by uschmidt          #+#    #+#             */
/*   Updated: 2024/11/28 13:43:27 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	ssize_t		read_bytes;
	static void	*buffer;
	int			buffer_size;

	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	read_bytes = read(fd, buffer, BUFFER_SIZE);
	return (buffer);
}

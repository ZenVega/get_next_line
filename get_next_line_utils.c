/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 12:43:28 by uschmidt          #+#    #+#             */
/*   Updated: 2024/12/04 14:32:24 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*s;
	unsigned char	*d;
	size_t			i;

	if (!dest && !src)
		return (dest);
	s = (unsigned char *)src;
	d = (unsigned char *)dest;
	i = -1;
	if (d > s)
		while (n-- > 0)
			d[n] = s[n];
	else
		while (++i < n)
			d[i] = s[i];
	return (dest);
}

size_t	ft_strlen(const char *str)
{
	ssize_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

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

char	*free_all(char **first, char **second)
{
	if (second != NULL)
		free(*second);
	free(*first);
	*first = NULL;
	return (*first);
}

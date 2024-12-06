/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:14:30 by uschmidt          #+#    #+#             */
/*   Updated: 2024/12/05 15:07:09 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*ptr;
	int				test;
	int				i;

	test = nmemb * size;
	if (size != 0 && test / size != nmemb)
		return (NULL);
	ptr = (unsigned char *)malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < test)
		ptr[i++] = 0;
	return ((void *)ptr);
}

char	*free_all(char *first, char *second)
{
	if (first)
	{
		free(first);
		first = NULL;
	}
	if (second)
	{
		free(second);
		second = NULL;
	}
	return (NULL);
}

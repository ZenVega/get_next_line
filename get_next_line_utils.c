/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 12:43:28 by uschmidt          #+#    #+#             */
/*   Updated: 2024/12/03 17:50:18 by uschmidt         ###   ########.fr       */
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

size_t	ft_strlen(const char *str, ssize_t bytes)
{
	ssize_t	i;

	i = 0;
	if (bytes)
		while (i < bytes && str[i])
			i++;
	else
		while (str[i])
			i++;
	return (i);
}

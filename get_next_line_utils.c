/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetit <lpetit@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 19:39:04 by lpetit            #+#    #+#             */
/*   Updated: 2023/11/02 08:55:26 by lpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include <stdlib.h>

size_t	ft_strlen(char *str)
{
	size_t	count;

	while (*str)
	{
		str++;
		count++;
	}
	return (count);
}

char	*ft_strchr(char const *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if ((unsigned char)c == '\0' && *s == '\0')
		return ((char *)s);
	return (NULL);
}

static void	ft_bzero(void *s, size_t n)
{
	unsigned char	*s_byte;

	s_byte = (unsigned char *)s;
	while (n > 0)
	{
		*s_byte++ = 0;
		n--;
	}
	return ;
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*dest;
	size_t	limit;

	dest = NULL;
	limit = nmemb * size;
	if (limit != 0 && size != 0)
	{
		if (limit / size != nmemb)
		{
			return (NULL);
		}
	}
	if (nmemb == 0 || size == 0)
		limit = 0;
	dest = (void *)malloc(limit);
	if (!dest)
		return (NULL);
	ft_bzero(dest, nmemb * size);
	return (dest);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetit <lpetit@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 19:39:04 by lpetit            #+#    #+#             */
/*   Updated: 2023/11/04 14:00:58 by lpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include <stdlib.h>

size_t	ft_strlen(char const *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i])
		i++;
	return (i);
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*jstr;
	size_t	i;

	i = 0;
	jstr = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!jstr)
		return (NULL);
	if (s1)
		while (*s1)
			jstr[i++] = *s1++;
	if (s2)
		while (*s2)
			jstr[i++] = *s2++;
	jstr[i] = '\0';
	return (jstr);
}

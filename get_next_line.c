/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetit <lpetit@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:30:29 by lpetit            #+#    #+#             */
/*   Updated: 2023/11/04 15:30:08 by lpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"
#include <stdio.h>

char	*ft_join_buffer(char *static_buf, char *buffer)
{
	char	*joined_buf;

	joined_buf = ft_strjoin(static_buf, buffer);
	free(static_buf);
	return (joined_buf);
}

char	*ft_next_line(char *buffer)
{
	char	*next;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\0')
	{
		free(buffer);
		return (NULL);
	}
	next = ft_calloc((ft_strlen(buffer) - i + 1), sizeof(char));
	if (!next)
	{
		free(buffer);
		return (NULL);
	}
	i++;
	while (buffer[i])
		next[j++] = buffer[i++];
	free(buffer);
	next[j] = '\0';
	return (next);
}

char	*ft_line(char *buffer)
{
	char	*line;
	size_t	i;

	i = 0;
	if (buffer[i] == '\0')
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_calloc((i + 2), sizeof(char));
	if (!line)
	{
		free(buffer);
		return (NULL);
	}
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
	{
		line[i++] = '\n';
	}
	return (line);
}

char	*ft_read_file(int fd, char *static_buf)
{
	char	*buffer;
	ssize_t	n;

	if (!static_buf)
		static_buf = calloc(1, 1);
	buffer = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buffer)
		return (NULL);
	n = 1;
	while (n > 0)
	{
		n = read(fd, buffer, BUFFER_SIZE);
		if (n == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[n] = '\0';
		static_buf = ft_join_buffer(static_buf, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (static_buf);
}

char	*get_next_line(int fd)
{
	static char	*static_buf;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	static_buf = ft_read_file(fd, static_buf);
	if (!static_buf)
		return (NULL);
	line = ft_line(static_buf);
	static_buf = ft_next_line(static_buf);
	return (line);
}
/*
#include <fcntl.h>
#include <stdio.h>
int	main(void)
{
	int	fd;
	char	*buffer;
	
	fd = open("test.txt", O_RDONLY | O_CREAT, 0666);
	if (fd == -1)
		printf("Error when opening file\n");
	buffer = get_next_line(fd);
	while (buffer)
	{
		printf("%s", buffer);
		printf("--------------\n");
		buffer = get_next_line(fd);
	}
	close(fd);
	free(buffer);
}*/

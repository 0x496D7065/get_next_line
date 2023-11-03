/* ************************************************************************** */

/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetit <lpetit@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:30:29 by lpetit            #+#    #+#             */
/*   Updated: 2023/11/02 07:06:29 by lpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"
#include <stdio.h>

char	*ft_next_line(char *buffer)
{
	char	*next;
	size_t	i;
	size_t	j;

	if (!buffer)
		return (NULL);
	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\0')
	{
		free(buffer);
		return (NULL);
	}
	next = (char *)malloc((ft_strlen(buffer) - (i + 1)) * sizeof(char));
	i = 0;
	while (buffer[j] != '\n')
		j++;
	j++;
	while (buffer[j])
		next[i++] = buffer[j++];
	free(buffer);
	next[i] = '\0';
	return (next);
}

char	*ft_line(char *buffer)
{
	char	*line;
	size_t	i;

	if (!buffer)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = (char *)malloc((i + 2) * sizeof(char));
	if (!line)
	{
		free(buffer);
		return (NULL);
	}
	i = 0;
	printf("In function buffer char =%c\n", buffer[0]);
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		printf("/%c", line[i]);
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
	{
		line[i++] = '\n';
		line[i] = '\0';
	}
	printf("\nin function line =%s\n", line);
	return (line);
}

char	*ft_read_file(int fd, char *buffer)
{
	ssize_t n;

	if (!buffer)
		buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	n = 1;
	while (n > 0)
	{
		n = read(fd, buffer, BUFFER_SIZE);
		//printf("in function =%s\n", buffer);
		if (n == -1)
		{
			free(buffer);
			return (NULL);
		}
		if (n == 0)
			break ;
		//printf("In read n =%ld\n", n);
		buffer[n] = '\0';
		//printf("In read after =%c\n", buffer[0]);
	}
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	
	buffer = ft_read_file(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_line(buffer);
	buffer = ft_next_line(buffer);
	return (line);
}

#include <fcntl.h>
int	main(void)
{
	int	fd;
	char	*buffer;
	
	fd = open("test.txt", O_RDONLY | O_CREAT, 0666);
	if (fd == -1)
		printf("Error when opening file\n");
	buffer = get_next_line(fd);
	//printf("%s\n", buffer);
	buffer = get_next_line(fd);
	printf("--------------\n");
	//printf("%s\n", buffer);
	buffer = get_next_line(fd);
	printf("--------------\n");
	//printf("%s\n", buffer);
	close(fd);
	free(buffer);
}

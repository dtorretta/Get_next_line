/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtorrett <dtorrett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:47:38 by dtorrett          #+#    #+#             */
/*   Updated: 2023/12/13 19:39:54 by dtorrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*set_line(char **line_buffer)
{
	char	*remaining;
	char	*temp;

	temp = ft_strchr(*line_buffer, '\n');
	if (!temp++)
		return (NULL);
	remaining = ft_strdup(temp);
	*temp = '\0';
	return (remaining);
}

char	*set_buffer(int fd, char *left_c)
{
	static char	buffer[BUFFER_SIZE + 1];
	int			bytesread;

	while (!ft_strchr(left_c, '\n'))
	{
		bytesread = read(fd, buffer, BUFFER_SIZE);
		if (bytesread == -1)
		{
			free(left_c);
			return (NULL);
		}
		if (bytesread == 0)
			break ;
		buffer[bytesread] = '\0';
		left_c = ft_strjoin(left_c, buffer);
	}
	return (left_c);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = set_buffer(fd, buffer);
	buffer = set_line(&line);
	return (line);
}
/*
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd1;
	char	*line;
	int		i;

	i = 0;
	fd1 = open("dict.txt", O_RDONLY);
	if (fd1 == -1)
	{
		return (1);
	}
	while (i < 1)
	{
		line = get_next_line(fd1);
		if (line == NULL)
			break ;
		printf("get line %d: %s\n", i + 1, line);
		free(line);
		i++;
	}
	close(fd1);
	return (0);
}*/

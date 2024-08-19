/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtorrett <dtorrett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 19:20:59 by dtorrett          #+#    #+#             */
/*   Updated: 2024/01/22 21:53:47 by dtorrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

char	*set_buffer(int fd, char *left_c, char *tempbuf)
{
	int	bytesread;

	while (!ft_strchr(left_c, '\n'))
	{
		bytesread = read(fd, tempbuf, BUFFER_SIZE);
		if (bytesread == -1)
		{
			free(left_c);
			return (NULL);
		}
		if (bytesread == 0)
			break ;
		tempbuf[bytesread] = '\0';
		left_c = ft_strjoin(left_c, tempbuf);
	}
	free(tempbuf);
	return (left_c);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffer[MAX_FD];
	char		*tempbuf;

	tempbuf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!tempbuf || fd < 0 || BUFFER_SIZE <= 0)
	{
		free(tempbuf);
		free(buffer[fd]);
		return (NULL);
	}
	line = set_buffer(fd, buffer[fd], tempbuf);
	buffer[fd] = set_line(&line);
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
	while (i < 10)
	{
		line = get_next_line(fd1);
		if (line == NULL)
			break ;
		printf("get line %d: %s", i + 1, line);
		free(line);
		i++;
	}
	close(fd1);
	return (0);
}*/

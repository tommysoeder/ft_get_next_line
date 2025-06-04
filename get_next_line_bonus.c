/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomamart <tomamart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:53:43 by tomamart          #+#    #+#             */
/*   Updated: 2025/06/04 12:09:25 by tomamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stddef.h>
#include "get_next_line.h"

char	*read_store(int fd, char *stash)
{
	char	*buffer;
	char	*tmp;
	int		bytes_read;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(stash, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(stash);
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		tmp = stash;
		stash = ft_strjoin(stash, buffer);
		free(tmp);
		if (!stash)
			return (free(buffer), NULL);
	}
	return (free(buffer), stash);
}

char	*extract_line(char *stash)
{
	char	*line;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	while (stash[i] != '\n' && stash[i])
		i++;
	if (stash[i] == '\n')
		len = i + 2;
	else
		len = i + 1;
	line = (char *)malloc(sizeof(char) * len);
	if (!line)
		return (NULL);
	while (stash[j] && stash[j] != '\n')
	{
		line[j] = stash[j];
		j++;
	}
	if (stash[j] == '\n')
		line[j++] = '\n';
	line[j] = '\0';
	return (line);
}

char	*store_rest(char *stash)
{
	int		i;
	int		j;
	char	*rest;

	i = 0;
	j = 0;
	while (stash[i] != '\n' && stash[i])
		i++;
	if (!stash[i])
		return (free(stash), NULL);
	i++;
	rest = (char *)malloc(ft_strlen(&stash[i]) + 1);
	if (!rest)
		return (free(stash), NULL);
	while (stash[i])
		rest[j++] = stash[i++];
	rest[j] = '\0';
	free(stash);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*stash[1024];
	char		*line;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	stash[fd] = read_store(fd, stash[fd]);
	if (!stash[fd] || stash[fd][0] == '\0')
		return (free(stash[fd]), stash[fd] = NULL, NULL);
	line = extract_line(stash[fd]);
	stash[fd] = store_rest(stash[fd]);
	return (line);
}

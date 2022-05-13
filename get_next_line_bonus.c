/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sryou <sryou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:57:36 by sryou             #+#    #+#             */
/*   Updated: 2022/05/13 15:08:29 by sryou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <unistd.h>

char	*ft_free(char **str1, char **str2)
{
	if (str1 != 0 && *str1 != 0)
	{
		free(*str1);
		*str1 = 0;
	}
	if (str2 != 0 && *str2 != 0)
	{
		free(*str2);
		*str2 = 0;
	}
	return (0);
}

int	find_newline_idx(char *line)
{
	int	idx;

	if (line[0] == '\0')
		return (-1);
	idx = 0;
	while (line[idx])
	{
		if (line[idx] == '\n')
			return (idx);
		idx++;
	}
	return (idx);
}

char	*make_remainline(char *line, int remainline_idx)
{
	char	*remainline;
	int		idx;

	if (ft_strlen(line) <= remainline_idx)
		remainline = (char *)malloc(sizeof(char) * 1);
	else
		remainline = (char *)malloc(sizeof(char) * \
			(ft_strlen(line) - remainline_idx + 2));
	if (remainline == 0)
		return (0);
	idx = 0;
	while (idx + remainline_idx <= ft_strlen(line))
	{
		remainline[idx] = line[idx + remainline_idx];
		idx++;
	}
	remainline[idx] = '\0';
	return (remainline);
}

char	*cut_line(char **line, int newline_idx)
{
	char	*newline;
	char	*remainline;

	newline = (char *)malloc(sizeof(char) * (newline_idx + 2));
	if (newline == 0)
		return (0);
	newline[0] = '\0';
	ft_strlcat(newline, *line, newline_idx + 2);
	remainline = make_remainline(*line, newline_idx + 1);
	if (remainline == 0)
		return (0);
	free(*line);
	*line = remainline;
	return (newline);
}

char	*get_next_line(int fd)
{
	static char	*line[OPEN_MAX];
	char		*buffer;
	int			newline_idx;
	int			readn;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0 || BUFFER_SIZE >= B_MAX)
		return (0);
	while (1)
	{
		buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buffer == 0)
			return (0);
		readn = read(fd, buffer, BUFFER_SIZE);
		if (readn < 0)
			return (ft_free(&buffer, &line[fd]));
		buffer[readn] = '\0';
		line[fd] = ft_strjoin(line[fd], buffer);
		if (line[fd] == 0)
			return (0);
		newline_idx = find_newline_idx(line[fd]);
		if (newline_idx == -1)
			return (ft_free(&line[fd], 0));
		if (readn == 0 || newline_idx != ft_strlen(line[fd]))
			return (cut_line(&line[fd], newline_idx));
	}
}

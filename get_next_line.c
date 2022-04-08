/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sryou <sryou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:57:36 by sryou             #+#    #+#             */
/*   Updated: 2022/04/08 18:28:29 by sryou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

int	check_newline(char *line)
{
	int	idx;

	idx = 0;
	while (line[idx])
	{
		if (line[idx] == '\n')
			return (idx);
		idx++;
	}
	return (-1);
}

char	*cut_line(char **line, int newline_idx)
{
	char	*res;
	char	*cutted_line;
	int		cutted_line_size;

	res = (char *)malloc(sizeof(char) * (newline_idx + 2));
	if (res == 0)
		return (0);
	ft_strstncpy(res, *line, 0, newline_idx);
	res[newline_idx] = '\n';
	res[newline_idx + 1] = '\0';
	cutted_line_size = ft_strlen(*line) - newline_idx;
	if (cutted_line_size <= 1)
	{
		if (*line != 0)
			free(*line);
		*line = 0;
	}
	else
	{
		cutted_line = (char *)malloc(sizeof(char) * (cutted_line_size));
		ft_strstncpy(cutted_line, *line, newline_idx + 1, cutted_line_size - 1);
		cutted_line[cutted_line_size] = '\0';
		free(*line);
		line = &cutted_line;
	}
	return (res);
}

char	*finish_read(char **line, int readn)
{
	int	newline_idx;

	if (readn < 0)
		return (0);
	newline_idx = check_newline(*line);
	if (newline_idx == -1)
		newline_idx = ft_strlen(*line);
	return (cut_line(line, newline_idx));
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*buffer;
	int			readn;
	int			newline_idx;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE == 2147483647)
		return (0);
	while (1)
	{
		buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buffer == 0)
			return (0);
		readn = read(fd, buffer, BUFFER_SIZE);
		if (readn <= 0)
			break ;
		buffer[readn] = '\0';
		line = ft_strjoin(line, buffer);
		if (line == 0)
			return (0);
		newline_idx = check_newline(line);
		if (newline_idx > -1)
			return (cut_line(&line, newline_idx));
	}
	return (finish_read(&line, readn));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sryou <sryou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:57:36 by sryou             #+#    #+#             */
/*   Updated: 2022/05/20 11:38:08 by sryou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

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

char	*make_remainline(char *line, int remainline_idx, int line_len)
{
	char	*remainline;
	int		idx;

	if (line_len <= remainline_idx)
		remainline = (char *)malloc(sizeof(char) * 1);
	else
		remainline = (char *)malloc(sizeof(char) * \
			(line_len - remainline_idx + 2));
	if (remainline == 0)
		return (0);
	idx = 0;
	while (idx + remainline_idx <= line_len)
	{
		remainline[idx] = line[idx + remainline_idx];
		idx++;
	}
	remainline[idx] = '\0';
	return (remainline);
}

char	*cut_line(char **line, int newline_idx, int line_len)
{
	char	*newline;
	char	*remainline;

	newline = (char *)malloc(sizeof(char) * (newline_idx + 2));
	if (newline == 0)
		return (0);
	newline[0] = '\0';
	ft_strmycat(newline, *line, 0, newline_idx + 1);
	remainline = make_remainline(*line, newline_idx + 1, line_len);
	if (remainline == 0)
		return (ft_free(line));
	ft_free(line);
	*line = remainline;
	return (newline);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		buffer[BUFFER_SIZE + 1];
	int			readn;
	int			newline_idx;
	int			line_len;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= B_MAX)
		return (0);
	while (1)
	{
		readn = read(fd, buffer, BUFFER_SIZE);
		if (readn < 0)
			return (ft_free(&line));
		buffer[readn] = '\0';
		line_len = ft_strjoin(&line, buffer);
		if (line_len == 0)
			return (ft_free(&line));
		newline_idx = find_newline_idx(line);
		if (newline_idx == -1)
			return (ft_free(&line));
		if (readn == 0 || newline_idx != line_len)
			return (cut_line(&line, newline_idx, line_len));
	}
}

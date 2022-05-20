/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sryou <sryou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:38:45 by sryou             #+#    #+#             */
/*   Updated: 2022/05/20 11:17:50 by sryou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# ifndef B_MAX
#  define B_MAX 2147483648
# endif

char	*get_next_line(int fd);
char	*ft_free(char **line);
int		ft_strlen(char *str);
void	ft_strmycat(char *dst, char *src, int dstsize, int srcsize);
int		ft_strjoin(char **line, char *buffer);

#endif
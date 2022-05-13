/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sryou <sryou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 18:02:05 by sryou             #+#    #+#             */
/*   Updated: 2022/05/13 14:12:19 by sryou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_strlen(char *str)
{
	int	idx;

	if (str == 0)
		return (0);
	idx = 0;
	while (str[idx])
		idx++;
	return (idx);
}

int	ft_strlcat(char *dst, char *src, int dstsize)
{
	int	idx;
	int	src_len;
	int	dst_len;

	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	if (dstsize == 0)
		return (src_len);
	if (dst_len >= dstsize)
		return (dstsize + src_len);
	idx = dst_len;
	dst = dst + dst_len;
	while (*src != '\0' && idx + 1 < dstsize)
	{
		*dst = *src;
		dst++;
		src++;
		idx++;
	}
	*dst = '\0';
	return (dst_len + src_len);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		len1;
	int		len2;
	char	*mkstr;

	if (s1 == 0 && s2 == 0)
		return (0);
	if (s1 == 0)
		return (s2);
	if (s2 == 0)
		return (s1);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	mkstr = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (mkstr == 0)
		return (0);
	mkstr[0] = '\0';
	ft_strlcat(mkstr, s1, len1 + 1);
	ft_strlcat(mkstr, s2, len1 + len2 + 1);
	free(s1);
	free(s2);
	return (mkstr);
}

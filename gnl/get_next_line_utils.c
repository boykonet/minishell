/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 16:44:40 by gkarina           #+#    #+#             */
/*   Updated: 2020/07/03 16:44:40 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t					ft_strlen(const char *s)
{
	int					i;

	i = 0;
	if (s == NULL || *s == '\0')
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char					*ft_strjoin(char const *s1, char const *s2)
{
	char				*dst;
	size_t				strlen1;
	size_t				strlen2;
	size_t				count;

	count = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	strlen1 = ft_strlen(s1);
	strlen2 = ft_strlen(s2);
	dst = (char*)malloc(sizeof(char) + (strlen1 + strlen2 + 1));
	if (dst == NULL)
		return (NULL);
	while (*s1)
		dst[count++] = *s1++;
	while (*s2)
		dst[count++] = *s2++;
	dst[count] = '\0';
	return (dst);
}

char					*ft_strchr(const char *s, int c)
{
	unsigned char		ch;
	char				*str;

	ch = (unsigned char)c;
	str = (char*)s;
	if (str == NULL)
		return (NULL);
	while (*str)
	{
		if (*str == ch)
			return (str);
		str++;
	}
	if (*str == ch)
		return (str);
	return (NULL);
}

char					*ft_strdup(const char *s1)
{
	char				*dupl;
	int					count;

	if (s1 == NULL)
		return (NULL);
	count = ft_strlen(s1);
	if ((dupl = (char*)malloc(sizeof(char) * (count + 1))) == NULL)
		return (NULL);
	count = 0;
	while (s1[count] != '\0')
	{
		dupl[count] = s1[count];
		count++;
	}
	dupl[count] = '\0';
	return (dupl);
}

size_t					ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				size;
	size_t				lensrc;

	d = (unsigned char*)dst;
	s = (const unsigned char*)src;
	size = dstsize;
	if (s == NULL || d == NULL)
		return (0);
	lensrc = ft_strlen(src);
	if (size)
	{
		while (--size && *s)
			*d++ = *s++;
		*d = '\0';
	}
	if (size == 0)
	{
		if (dstsize != 0)
			*d = '\0';
	}
	return (lensrc);
}

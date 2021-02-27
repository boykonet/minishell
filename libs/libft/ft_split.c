/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 18:44:11 by gkarina           #+#    #+#             */
/*   Updated: 2020/05/10 18:44:11 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		*ft_split_free(char **dst)
{
	size_t	i;

	i = 0;
	while (dst[i] != NULL)
	{
		free(dst[i]);
		i++;
	}
	free(dst);
	return (NULL);
}

static size_t	ft_split_count(const char *s, const char c)
{
	size_t		i;
	size_t		count;

	i = 0;
	count = 0;
	if (s[i] == '\0')
		return (count);
	while (s[i] != '\0')
	{
		if (s[i] != c && s[i] != '\0')
		{
			count++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
		while (s[i] == c && s[i] != '\0')
			i++;
	}
	return (count);
}

static char		**ft_split_log(char **d, char const *s, const char v, size_t ch)
{
	char const	*src;
	size_t		i;
	size_t		count;

	src = s;
	i = 0;
	while (ch > i && *s != '\0')
	{
		if (*src != v && *src != '\0')
		{
			while (*src != v && *src != '\0')
				src++;
			count = src - s;
			if ((d[i] = (char*)malloc(sizeof(char) * (count + 1))) == NULL)
			{
				ft_split_free(d);
				return (NULL);
			}
			d[i] = ft_memcpy(d[i], s, count);
			d[i++][count] = '\0';
		}
		s = ++src;
	}
	d[i] = NULL;
	return (d);
}

char			**ft_split(char const *s, char c)
{
	char		**dst;
	size_t		ch;

	if (s == NULL)
		return (0);
	ch = ft_split_count(s, c);
	if ((dst = (char**)malloc(sizeof(char*) * (ch + 1))) == NULL)
		return (NULL);
	if ((dst = ft_split_log(dst, s, c, ch)) == NULL)
		return (NULL);
	return (dst);
}

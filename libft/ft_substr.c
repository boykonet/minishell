/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 16:33:46 by gkarina           #+#    #+#             */
/*   Updated: 2020/05/10 16:33:46 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_substr_logic(char const *s, unsigned int start, size_t len)
{
	char const	*src;
	char		*dst;
	size_t		size;
	size_t		count;

	count = 0;
	src = s;
	size = len;
	while (start-- && *src != '\0')
		src++;
	s = src;
	while (size-- && *src++)
		count++;
	if ((dst = (char*)malloc(sizeof(char) * (count + 1))) == NULL)
		return (NULL);
	count = 0;
	while (len-- && *s != '\0')
		dst[count++] = *s++;
	dst[count] = '\0';
	return (dst);
}

char		*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*dst;
	size_t		lens;

	if (s == NULL)
		return (NULL);
	lens = ft_strlen(s);
	if (start > lens || len == 0 || *s == '\0')
	{
		if ((dst = (char*)malloc(sizeof(char) * 1)) == NULL)
			return (NULL);
		dst[0] = '\0';
		return (dst);
	}
	else
	{
		if ((dst = ft_substr_logic(s, start, len)) == NULL)
			return (NULL);
	}
	return (dst);
}

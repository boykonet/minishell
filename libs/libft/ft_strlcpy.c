/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 00:21:05 by gkarina           #+#    #+#             */
/*   Updated: 2020/05/02 00:21:05 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
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

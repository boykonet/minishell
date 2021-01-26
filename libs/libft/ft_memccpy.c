/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 18:46:08 by gkarina           #+#    #+#             */
/*   Updated: 2020/04/30 18:46:08 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	unsigned char		ch;

	d = (unsigned char*)dst;
	s = (const unsigned char*)src;
	ch = (unsigned char)c;
	if (s == NULL || d == NULL)
		return (NULL);
	while (n)
	{
		*d++ = *s;
		if (*s == ch)
			return (d);
		s++;
		n--;
	}
	return (NULL);
}

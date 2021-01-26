/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 22:42:47 by gkarina           #+#    #+#             */
/*   Updated: 2020/05/05 22:42:47 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	ch;
	char			*str;
	size_t			len;

	ch = (unsigned char)c;
	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	str = (char*)&s[len];
	if (*str == '\0' && ch == '\0')
		return (str);
	while (len)
	{
		str--;
		len--;
		if (*str == ch)
			return (str);
	}
	return (NULL);
}

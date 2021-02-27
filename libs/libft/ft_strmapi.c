/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 21:12:15 by gkarina           #+#    #+#             */
/*   Updated: 2020/05/10 21:12:15 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*dst;
	size_t	len;
	size_t	count;

	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	if ((dst = (char*)malloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	count = 0;
	while (count < len)
	{
		dst[count] = f(count, s[count]);
		count++;
	}
	dst[count] = '\0';
	return (dst);
}

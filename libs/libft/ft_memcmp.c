/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 10:50:30 by gkarina           #+#    #+#             */
/*   Updated: 2020/05/06 10:50:30 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*str1;
	const unsigned char	*str2;

	str1 = (const unsigned char*)s1;
	str2 = (const unsigned char*)s2;
	if (str1 == NULL || str2 == NULL)
		return (0);
	if (n == 0)
		return (0);
	else if (n > 1)
	{
		while (--n && (*str1 == *str2))
		{
			str1++;
			str2++;
		}
	}
	return (*str1 - *str2);
}

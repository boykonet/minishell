/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 17:56:20 by gkarina           #+#    #+#             */
/*   Updated: 2020/05/10 17:56:20 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	size_t	strlen1;
	size_t	strlen2;
	size_t	count;

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

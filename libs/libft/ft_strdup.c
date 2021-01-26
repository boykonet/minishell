/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 14:59:36 by gkarina           #+#    #+#             */
/*   Updated: 2020/05/04 14:59:36 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dupl;
	int		count;

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

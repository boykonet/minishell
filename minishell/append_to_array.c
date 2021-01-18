/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_to_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 22:34:35 by gkarina           #+#    #+#             */
/*   Updated: 2021/01/18 22:34:35 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char		*append_to_array(char *src, char symb)
{
	char 	*dst;
	int 	i;

	i = 0;
	if (!(dst = ft_calloc(ft_strlen(src) + 2, sizeof(char))))
		exit(errno);
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = symb;
	dst[++i] = '\0';
	return (dst);
}

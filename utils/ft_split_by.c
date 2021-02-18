/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_by.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 03:21:11 by gkarina           #+#    #+#             */
/*   Updated: 2021/02/18 03:21:11 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		*ft_split_by_quation(char *str, t_env *lst, char c)
{
	char	*tmp;

	tmp = ft_strchr(str, c);
	lst->name = ft_substr(str, 0, tmp - str);
	if (*(tmp + 1) == '\0')
		lst->value = ft_strdup("");
	else
		lst->value = ft_substr(tmp, 1, ft_strlen(str));
	if (!lst->name || !lst->value)
		exit(errno);
	return (tmp);
}

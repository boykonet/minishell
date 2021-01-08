/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 01:15:50 by gkarina           #+#    #+#             */
/*   Updated: 2021/01/09 01:15:50 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int 		redirects(t_list **curr)
{
	if (!ft_strncmp((*curr)->content, "<", ft_strlen((*curr)->content)) || \
		!ft_strncmp((*curr)->content, ">", ft_strlen((*curr)->content)) || \
		!ft_strncmp((*curr)->content, ">>", ft_strlen((*curr)->content)) || \
		!ft_strncmp((*curr)->content, "1>", ft_strlen((*curr)->content)) || \
		!ft_strncmp((*curr)->content, "1>>", ft_strlen((*curr)->content)) ||
		!ft_strncmp((*curr)->content, "2>", ft_strlen((*curr)->content)) || \
		!ft_strncmp((*curr)->content, "2>>", ft_strlen((*curr)->content)))
	{
		return (1);
	}
	return (0);
}

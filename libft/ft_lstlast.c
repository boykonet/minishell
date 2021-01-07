/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 20:49:01 by gkarina           #+#    #+#             */
/*   Updated: 2020/05/11 20:49:01 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list *current;

	current = lst;
	if (current == NULL)
		return (NULL);
	else
	{
		if (current->next == NULL)
			return (current);
		while (current->next != NULL)
			current = current->next;
	}
	return (current);
}

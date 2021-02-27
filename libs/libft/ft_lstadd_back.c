/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 14:05:45 by gkarina           #+#    #+#             */
/*   Updated: 2020/05/12 14:05:45 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current;
	t_list	*prev;

	current = (*lst);
	prev = (*lst);
	if (current == NULL)
		(*lst) = new;
	else
	{
		while (current != NULL)
		{
			prev = current;
			current = current->next;
		}
		prev->next = new;
	}
}

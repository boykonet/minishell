/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 20:33:48 by gkarina           #+#    #+#             */
/*   Updated: 2020/05/11 20:33:48 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstsize(t_list *lst)
{
	t_list	*current;
	int		size;

	size = 0;
	current = lst;
	if (current == NULL)
		return (0);
	else
	{
		while (current != NULL)
		{
			current = current->next;
			size++;
		}
	}
	return (size);
}

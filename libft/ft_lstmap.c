/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 14:49:00 by gkarina           #+#    #+#             */
/*   Updated: 2020/05/13 14:49:00 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*current;
	t_list	*prev;
	t_list	*node;
	void	*new_content;

	current = lst;
	if (lst == NULL)
		return (NULL);
	if ((head = ft_lstnew((*f)(current->content))) == NULL)
		return (NULL);
	current = current->next;
	while (current != NULL)
	{
		prev = current;
		current = current->next;
		new_content = (*f)(prev->content);
		if ((node = ft_lstnew(new_content)) == NULL)
		{
			ft_lstclear(&head, del);
			return (NULL);
		}
		ft_lstadd_back(&head, node);
	}
	return (head);
}

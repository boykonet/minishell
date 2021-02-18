/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 03:21:31 by gkarina           #+#    #+#             */
/*   Updated: 2021/02/18 03:21:31 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "other.h"

void			lst_delete(t_list **head, t_list *d)
{
	t_list		**elem;

	elem = head;
	while (elem && (*elem) && (*elem) != d)
		elem = &(*elem)->next;
	if (elem && *elem)
	{
		*elem = (*elem)->next;
		del_list_content(d->content);
		free(d);
	}
}

void			lst_replase(t_list **head, t_list **list, t_list *d)
{
	t_list		**curr;

	curr = head;
	while (curr && (*curr) && (*curr) != d)
		curr = &(*curr)->next;
	if (curr && *curr && list)
	{
		*curr = *list;
		while ((*curr)->next)
			curr = &(*curr)->next;
		(*curr)->next = d->next;
		del_list_content(d->content);
		free(d);
	}
}

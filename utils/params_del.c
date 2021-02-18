/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_del.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 03:20:48 by gkarina           #+#    #+#             */
/*   Updated: 2021/02/18 03:20:48 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"

void			params_delete(t_params **head, t_params *d)
{
	t_params	**elem;

	elem = head;
	while (elem && (*elem) && (*elem) != d)
		elem = &(*elem)->next;
	if (elem && *elem)
	{
		*elem = (*elem)->next;
		del_params_content(d);
		free(d);
	}
}

t_params		*split_par(t_params **head, int len)
{
	t_params	*newhead;
	t_params	*curr;
	int			i;

	i = 0;
	newhead = (*head);
	curr = newhead;
	while (i < len)
	{
		(*head) = (*head)->next;
		i++;
	}
	while (curr && --len)
		curr = curr->next;
	if (curr)
		curr->next = NULL;
	return (newhead);
}

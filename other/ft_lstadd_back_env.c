/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_env.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 13:23:56 by gkarina           #+#    #+#             */
/*   Updated: 2021/02/08 13:23:56 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "other.h"

void		ft_lstadd_back_env(t_env **env, t_env *new)
{
	t_env	*current;
	t_env	*prev;

	current = (*env);
	prev = (*env);
	if (current == NULL)
		(*env) = new;
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

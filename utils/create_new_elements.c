/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_new_elements.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 23:53:17 by gkarina           #+#    #+#             */
/*   Updated: 2021/01/18 23:53:17 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "minishell.h"

t_env			*ft_lstnew_env(void *name, void *value)
{
	t_env		*new;

	if (!(new = malloc(sizeof(t_env))))
		exit(errno);
	new->name = name;
	new->value = value;
	new->next = NULL;
	return (new);
}

t_params		*new_params_element(void)
{
	t_params	*params;

	if (!(params = malloc(sizeof(t_params))))
		exit(errno);
	init_params(&params);
	return (params);
}

t_env			*new_item(t_list *item)
{
	t_env		*random;

	random = ft_lstnew_env(NULL, NULL);
	if (ft_strchr(item->content, '='))
		ft_split_by_quation(item->content, random, '=');
	else
	{
		if (!(random->name = ft_strdup(item->content)))
			exit(errno);
	}
	return (random);
}

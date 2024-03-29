/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_params_in_struct.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 22:55:27 by gkarina           #+#    #+#             */
/*   Updated: 2020/12/17 22:55:27 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void			env_free(t_env **env, void (*del)(t_env *))
{
	t_env		*curr;

	while ((*env) != NULL)
	{
		curr = (*env)->next;
		if (del)
			(*del)((*env));
		free((*env));
		(*env) = curr;
	}
}

void			params_free(t_params **params, void (*del)(t_params *))
{
	t_params	*curr;

	while ((*params) != NULL)
	{
		curr = (*params)->next;
		if (del)
			(*del)((*params));
		free((*params));
		(*params) = curr;
	}
}

void			free_string(char **str)
{
	int			i;

	i = 0;
	while (str[i])
	{
		if (str[i])
			free(str[i]);
		i++;
	}
	free(str);
}

void			free_env_element(t_env *lst)
{
	if (!lst)
		return ;
	if (lst->name)
		free(lst->name);
	if (lst->value)
		free(lst->value);
	free(lst);
}

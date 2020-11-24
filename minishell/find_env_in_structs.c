/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 22:18:06 by gkarina           #+#    #+#             */
/*   Updated: 2020/11/23 22:18:06 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env		*find_env_in_structs(t_env *env, char *needle)
{
	t_env	*curr;

	curr = env;
	while (curr)
	{
		if (!ft_strncmp(curr->name, needle, ft_strlen(needle)))
			break ;
		curr = curr->next;
	}
	return (curr);
}

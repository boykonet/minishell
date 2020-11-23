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

char		*find_string(t_env *env, char *needle)
{
	t_list	*curr;
	char	*result;

	result = NULL;
	curr = list;
	while (curr)
	{
		if (!ft_strncmp(curr->content, needle, ft_strlen(needle)))
			break ;
		curr = curr->next;
	}
	if (!curr)
		return (NULL);
	if (!(result = ft_strdup(curr->content)))
		return (NULL);
	return (result);
}

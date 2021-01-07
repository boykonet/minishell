/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 00:11:07 by gkarina           #+#    #+#             */
/*   Updated: 2020/11/21 00:11:07 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list 			*parser(t_list *tokens, t_fd *fd)
{
	t_list		*res;
	t_list		*curr;
	t_params	*params;

	if (!(params = malloc(sizeof(t_params))))
		return (NULL);
	init_params(params);
	if (!(params->cmd = ft_strdup(tokens->content)))
	{
		
	}
	if (!(res = ft_lstnew(tokens->content)))
		return (NULL);
	tokens = tokens->next;
	curr = res;
	while (tokens)
	{
		curr->next =
		tokens = tokens->next;
	}
	return (res);
}
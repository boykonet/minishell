/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaomi <snaomi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 01:58:49 by snaomi            #+#    #+#             */
/*   Updated: 2021/02/09 08:22:58 by snaomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"
#include "builtins.h"

void			env_item_free(t_env **head, t_env *d)
{
	t_env		**elem;

	elem = head;
	while (elem && (*elem) && (*elem) != d)
		elem = &(*elem)->next;
	if (elem && *elem)
	{
		*elem = (*elem)->next;
		del_env_content(d);
		free(d);
	}
}

static void		del_if_found(char *name, t_env **env)
{
	t_env		*buf;

	buf = *env;
	while (buf)
	{
		if (!ft_strcmp(name, buf->name))
		{
			env_item_free(env, buf);
			break ;
		}
		buf = buf->next;
	}
}

int				ft_unset(t_env **env, t_params *argv)
{
	t_list		*list;
	int			status;

	status = 0;
	list = argv->args;
	while (list->next)
	{
		list = list->next;
		if (check_word(list))
			del_if_found(list->content, env);
		else
			status = print_notification(argv, list);
	}
	return (status);
}

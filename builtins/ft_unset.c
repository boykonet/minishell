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
#include "other.h"
#include "builtins.h"

static void		env_item_free(t_env *env, t_env *prev, void (*del)(t_env *))
{
	t_env	*curr;

	curr = env->next;
	if (del)
		(*del)(env);
	free(env);
	prev->next = curr;
}

static void		del_if_found(t_list *smth, t_env *buf, \
				t_env *buf_prev, t_env *buf_next)
{
	while (buf)
	{
		if (!ft_strcmp(smth->content, buf->name))
		{
			buf_next = buf->next;
			env_item_free(buf, buf_prev, del_env_content);
			buf = buf_next;
		}
		else if (buf)
		{
			buf_prev = buf;
			buf = buf->next;
		}
	}
}

int				ft_unset(t_env **env, t_params *argv)
{
	t_list		*smth;
	t_env		*buf;
	t_env		*buf_prev;
	t_env		*buf_next;
	int			status;

	status = 0;
	buf_prev = NULL;
	buf_next = NULL;
	smth = argv->args;
	while (smth->next)
	{
		buf = *env;
		smth = smth->next;
		if (check_word(smth))
			del_if_found(smth, buf, buf_prev, buf_next);
		else
			status = print_notification(argv, smth);
	}
	return (status);
}

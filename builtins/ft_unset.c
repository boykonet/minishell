/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaomi <snaomi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 01:58:49 by snaomi            #+#    #+#             */
/*   Updated: 2021/02/07 15:42:07 by snaomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "other.h"

static void		print_notification(t_params *argv)
{
	ft_putstr_fd("minishell: unset: `", 2);
	ft_putstr_fd(argv->args->content, 2);
	ft_putendl_fd("': not a valid identifier", 2);
}

static void		env_item_free(t_env *env, t_env *prev, void (*del)(t_env *))
{
	t_env	*curr;

	curr = env->next;
	if (del)
		(*del)(env);
	free(env);
	prev->next = curr;
}

int				ft_unset(t_env **env, t_params *argv)
{
	t_env		*prev;
	t_env		*buf;
	int			status;

	buf = *env;
	status = 0;
	while (argv->args->next)
	{
		argv->args = argv->args->next;
		if (check_word(argv->args))
		{
			while (buf)
			{
				if (!ft_strcmp(argv->args->content, buf->name))
					env_item_free(buf, prev, del_env_content);
				if (buf)
				{
					prev = buf;
					buf = buf->next;
				}
			}
		}
		else
		{
			print_notification(argv);
			status = 1;
		}
	}
	return (status);
}

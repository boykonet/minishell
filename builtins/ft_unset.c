/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaomi <snaomi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 01:58:49 by snaomi            #+#    #+#             */
/*   Updated: 2021/01/29 22:53:06 by snaomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "other.h"

void 			env_item_free(t_env *env, t_env *prev, void (*del)(t_env *))
{
	t_env		*curr;

	curr = env->next;
	if (del)
		(*del)(env);
	free(env);
	prev->next = curr;
}

int		ft_unset(t_env **env, t_params *argv)
{
	t_env 	*prev;
	t_env 	*buf;

	buf = *env;
    while (argv->args->next)
	{
		argv->args=argv->args->next;
        if(check_word(argv->args))
        {
            // random = new_item(argv->args);
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
            ft_putstr_fd("minishell: unset: `", 1);
            ft_putstr_fd(argv->args->content, 1);
            ft_putstr_fd("': not a valid identifier", 1);
            ft_putchar_fd('\n', 1);
        }
    }
    return (0);
}
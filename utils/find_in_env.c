/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_in_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 14:55:26 by gkarina           #+#    #+#             */
/*   Updated: 2021/02/08 14:55:26 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** 0 return value have name in needle, 1 return name have value in needle
*/

#include "utils.h"

char		*find_data_in_env(t_env *env, char *needle, int serial_num)
{
	char	*val;

	val = NULL;
	while (env)
	{
		if (env->name && serial_num == 0)
			val = env->name;
		else if (env->value && serial_num == 1)
			val = env->value;
		if (!ft_strcmp(val, needle))
			break ;
		env = env->next;
	}
	if (!env)
		return (NULL);
	if (serial_num == 0)
		return (env->value);
	return (env->name);
}

t_env		*find_list_env(t_env *env, char *needle, int spec)
{
	while (env)
	{
		if (!spec && !ft_strncmp(env->name, needle, ft_strlen(env->name)))
			return (env);
		else if (spec == 1 && !ft_strncmp(env->value, needle, \
				ft_strlen(env->value)))
			return (env);
		env = env->next;
	}
	return (NULL);
}

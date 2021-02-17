/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_envp_to_struct.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 14:56:21 by gkarina           #+#    #+#             */
/*   Updated: 2021/02/08 14:56:21 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "other.h"
#include "builtins.h"

static void		init_name_value(char *str, \
				char *separator, char **name, char **value)
{
	*name = ft_substr(str, 0, separator - str);
	*value = ft_substr(separator, 1, ft_strlen(separator + 1));
	if (!(*name) || !(*value))
		exit(errno);
}

void			add_params_env(t_env **curr, char *name, char *value)
{
	t_env		*new;

	if (name)
		if (!(name = ft_strdup(name)))
			exit(errno);
	if (value)
		if (!(value = ft_strdup(value)))
			exit(errno);
	new = ft_lstnew_env(name, value);
	ft_lstadd_back_env(curr, new);
}

t_env			*copy_envp_to_struct(char **envp)
{
	t_env		*env;
	t_env		*curr;
	char		*tmp;
	size_t		i;

	i = 0;
	env = ft_lstnew_env(NULL, NULL);
	curr = env;
	tmp = ft_strchr(envp[i], '=');
	init_name_value(envp[i], tmp, &curr->name, &curr->value);
	while (envp[++i])
	{
		curr->next = ft_lstnew_env(NULL, NULL);
		tmp = ft_strchr(envp[i], '=');
		init_name_value(envp[i], tmp, &curr->next->name, &curr->next->value);
		curr = curr->next;
	}
	if (!find_data_in_env(env, "OLDPWD", 0))
		add_params_env(&curr, "OLDPWD", NULL);
	if (!find_data_in_env(env, "HOME", 0))
		add_params_env(&curr, "HOME", "/");
	if (!find_data_in_env(env, "LOGNAME", 0))
		add_params_env(&curr, "LOGNAME", "logname");
	if (!find_data_in_env(env, "PWD", 0))
	{
		ft_pwd(&tmp);
		add_params_env(&curr, "PWD", tmp);
		free(tmp);
	}
	return (env);
}

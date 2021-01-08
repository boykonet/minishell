/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 20:57:36 by gkarina           #+#    #+#             */
/*   Updated: 2020/11/19 20:57:36 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		builtins(t_params *params, t_env *env, int *status)
{
	char	*str;
	char	*home;
	char	*pwd_curr;
	char	*old_pwd;

	str = NULL;
	find_data_in_env(env, "PWD", &pwd_curr, 0);
	find_data_in_env(env, "OLDPWD", &old_pwd, 0);
	find_data_in_env(env, "HOME", &home, 0);
	if (!pwd_curr || !old_pwd || !home)
		return ;
	if (!ft_strncmp(params->cmd, "echo", ft_strlen(params->cmd)))
		ft_echo(&params->args, env, return_value);

	else if (!ft_strncmp(params->cmd, "pwd", ft_strlen(params->cmd)))
		str = ft_pwd(str);

	else if (!ft_strncmp(params->cmd, "cd", ft_strlen(params->cmd)))
		return_value = ft_cd((params->args)->content, &home, &pwd_curr, &old_pwd);

	/* else if (!ft_strncmp(str->command, "export", 6)) */
	/* 	ft_export(); */

	/* else if (!ft_strncmp(str->command, "unset", 5)) */
	/* 	ft_unset(); */

	/* else if (!ft_strncmp(str->command, "env", 3)) */
	/* 	ft_env(); */

	/* else if (!ft_strncmp(str->command, "exit", 4)) */
	/* 	ft_exit(); */
}

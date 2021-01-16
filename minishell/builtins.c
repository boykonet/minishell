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

void		builtins(t_params *params, t_env **env, int *status)
{
	char	*str;

	str = NULL;
//	if (!ft_strncmp(params->args->content, "echo", ft_strlen(params->args->content)))
//		ft_echo(params->args, env, status);

	if (!ft_strncmp(params->args->content, "pwd", ft_strlen(params->args->content)))
		str = ft_pwd(str);

	else if (!ft_strncmp(params->args->content, "cd", ft_strlen(params->args->content)))
		ft_cd(params->args, env, status);

	/* else if (!ft_strncmp(str->command, "export", 6)) */
	/* 	ft_export(); */

	/* else if (!ft_strncmp(str->command, "unset", 5)) */
	/* 	ft_unset(); */

	/* else if (!ft_strncmp(str->command, "env", 3)) */
	/* 	ft_env(); */

	/* else if (!ft_strncmp(str->command, "exit", 4)) */
	/* 	ft_exit(); */
}

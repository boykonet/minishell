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

int         builtins(t_params *params, t_env **env, int *status)
{
	char	*str;

	str = NULL;
	if (!ft_strncmp(params->args->content, "echo", ft_strlen(params->args->content)))
		*status = ft_echo(params->args->next, params->out);

	else if (!ft_strncmp(params->args->content, "pwd", ft_strlen(params->args->content)))
	{
		*status = ft_pwd(&str);
		if (str)
		{
			ft_printf("%s\n", str);
			free(str);
		}
	}
	else if (!ft_strncmp(params->args->content, "cd", ft_strlen(params->args->content)))
		*status = ft_cd(params->args->next, env);

	/* else if (!ft_strncmp(str->command, "export", 6)) */
	/* 	ft_export(); */

	/* else if (!ft_strncmp(str->command, "unset", 5)) */
	/* 	ft_unset(); */

	/* else if (!ft_strncmp(str->command, "env", 3)) */
	/* 	ft_env(); */

	else if (!ft_strncmp(params->args->content, "exit", ft_strlen(params->args->content)))
	{
		if (!ft_exit())
			return (0);
	}
	return (1);
}

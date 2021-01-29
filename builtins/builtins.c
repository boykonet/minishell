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

#include "builtins.h"
#include "minishell.h"
#include "other.h"

static int	seven_commands(t_params *params, t_env **env, int *status)
{
	char 	*str;

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
	else if (!ft_strncmp(params->args->content, "export", ft_strlen(params->args->content)))
		ft_export(env, params);
	else if (!ft_strncmp(params->args->content, "unset", ft_strlen(params->args->content)))
		ft_unset(env, params);
	else if (!ft_strncmp(params->args->content, "env", ft_strlen(params->args->content)))
		ft_env(env, params);
	else if (!ft_strncmp(params->args->content, "exit", ft_strlen(params->args->content)))
		if (!ft_exit())
			return (0);
	return (1);
}

int         builtins(t_params *params, t_env **env, int *status)
{
	char	**arr;
	char	*cmd;

	if (!check_command(params->args->content))
	{
		if (!seven_commands(params, env, status))
			return (0);
	}
	else
	{
		arr = convert_struct_to_array(params->args);
		if (!(cmd = find_path(params->args->content, find_data_in_env(*env, "PATH", 0))))
			cmd = ft_strdup(params->args->content);
		*status = create_process(arr, cmd);
		free_string(arr);
		free(cmd);
	}
	return (1);
}
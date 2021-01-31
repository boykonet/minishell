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

static int	seven_commands(t_params *params, t_env **env, int *exit_status)
{
	char 	*str;
	int 	stat;

	str = NULL;
	stat = 0;
	if (!ft_strncmp(params->args->content, "echo", ft_strlen(params->args->content)))
		stat = ft_echo(params->args->next, params->out);
	else if (!ft_strncmp(params->args->content, "pwd", ft_strlen(params->args->content)))
		stat = ft_pwd(&str);
	else if (!ft_strncmp(params->args->content, "cd", ft_strlen(params->args->content)))
		stat = ft_cd(params->args->next, env, params->out);
	else if (!ft_strncmp(params->args->content, "export", ft_strlen(params->args->content)))
		stat = ft_export(env, params);
	else if (!ft_strncmp(params->args->content, "unset", ft_strlen(params->args->content)))
		stat = ft_unset(env, params);
	else if (!ft_strncmp(params->args->content, "env", ft_strlen(params->args->content)))
		stat = ft_env(env, params);
	else if (!ft_strncmp(params->args->content, "exit", ft_strlen(params->args->content)))
	{
		stat = ft_exit(params->args->next);
		*exit_status = 1;
	}
	if (str)
	{
		ft_putendl_fd(str, params->out);
		free(str);
	}
	return (stat);
}

int         builtins(t_params *params, t_env **env, int *status, int *exit_status)
{
	if (!find_data_in_env(*env, "PATH", 0))
	{
		ft_putstr_fd("-minishell: ", 1);
		ft_putstr_fd(params->args->content, 1);
		ft_putendl_fd(": command not found", 1);
		*status = 127;
	}
	if (!*status)
		*status = seven_commands(params, env, exit_status);
	return (*status);
}